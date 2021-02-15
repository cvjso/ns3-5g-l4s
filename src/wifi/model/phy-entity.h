/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 Orange Labs
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Rediet <getachew.redieteab@orange.com>
 *          Sébastien Deronne <sebastien.deronne@gmail.com> (for logic ported from wifi-phy)
 *          Mathieu Lacage <mathieu.lacage@sophia.inria.fr> (for logic ported from wifi-phy)
 */

#ifndef PHY_ENTITY_H
#define PHY_ENTITY_H

#include "wifi-mpdu-type.h"
#include "wifi-tx-vector.h"
#include "wifi-phy-band.h"
#include "wifi-ppdu.h"
#include "wifi-spectrum-signal-parameters.h"
#include "wifi-mpdu-type.h"
#include "ns3/event-id.h"
#include "ns3/simple-ref-count.h"
#include "ns3/nstime.h"
#include "ns3/wifi-spectrum-value-helper.h"
#include <list>
#include <map>

/**
 * \file
 * \ingroup wifi
 * Declaration of:
 * - ns3::PhyEntity class
 * - ns3::SignalNoiseDbm, ns3::MpduInfo, and ns3::RxSignalInfo structs
 * - ns3::RxPowerWattPerChannelBand typedef
 */

namespace ns3 {

/// SignalNoiseDbm structure
struct SignalNoiseDbm
{
  double signal; ///< signal strength in dBm
  double noise;  ///< noise power in dBm
};

/// MpduInfo structure
struct MpduInfo
{
  MpduType type;          ///< type of MPDU
  uint32_t mpduRefNumber; ///< MPDU ref number
};

/// RxSignalInfo structure containing info on the received signal
struct RxSignalInfo
{
  double snr;  ///< SNR in linear scale
  double rssi; ///< RSSI in dBm
};

/**
 * A map of the received power (Watts) for each band
 */
typedef std::map <WifiSpectrumBand, double> RxPowerWattPerChannelBand;

class WifiPsdu;
class WifiPhy;
class InterferenceHelper;
class Event;
class WifiPhyStateHelper;
class WifiPsdu;
class WifiPpdu;

/**
 * \brief Abstract class for PHY entities
 * \ingroup wifi
 *
 * This class enables to have a unique set of APIs
 * to be used by each PHY entity, corresponding to
 * the different amendments of the IEEE 802.11 standard.
 */
class PhyEntity : public SimpleRefCount<PhyEntity>
{
public:

  /**
   * Action to perform in case of RX failure.
   */
  enum PhyRxFailureAction
  {
    DROP = 0, //!< drop PPDU and set CCA_BUSY
    ABORT,    //!< abort reception of PPDU
    IGNORE    //!< ignore the reception
  };

  /**
   * Status of the reception of the PPDU field.
   */
  struct PhyFieldRxStatus
  {
    /* *NS_CHECK_STYLE_OFF* */
    bool isSuccess {true}; //!< outcome (\c true if success) of the reception
    WifiPhyRxfailureReason reason {UNKNOWN}; //!< failure reason
    PhyRxFailureAction actionIfFailure {DROP}; //!< action to perform in case of failure \see PhyRxFailureAction
    /**
     * Constructor setting outcome of reception.
     *
     * \param s \c true if success
     */
    PhyFieldRxStatus (bool s) : isSuccess (s) {};
    /**
     * Constructor.
     *
     * \param s \c true if success
     * \param r reason of failure
     * \param a action to perform in case of failure
     */
    PhyFieldRxStatus (bool s, WifiPhyRxfailureReason r, PhyRxFailureAction a) : isSuccess (s), reason (r), actionIfFailure (a) {};
    /* *NS_CHECK_STYLE_ON* */
  };

  /**
   * A struct for both SNR and PER
   */
  struct SnrPer
  {
    double snr {0.0}; ///< SNR in linear scale
    double per {1.0}; ///< PER
    /**
     * Default constructor.
     */
    SnrPer () {};
    /**
     * Constructor for SnrPer.
     *
     * \param s the SNR in linear scale
     * \param p the PER
     */
    SnrPer (double s, double p) : snr (s), per (p) {};
  };

  /**
   * Destructor for PHY entity
   */
  virtual ~PhyEntity ();

  /**
   * Set the WifiPhy owning this PHY entity.
   *
   * \param wifiPhy the WifiPhy owning this PHY entity
   */
  void SetOwner (Ptr<WifiPhy> wifiPhy);

  /**
   * Check if the WifiMode is supported.
   *
   * \param mode the WifiMode to check
   * \return true if the WifiMode is supported,
   *         false otherwise
   */
  virtual bool IsModeSupported (WifiMode mode) const;
  /**
   * \return the number of WifiModes supported by this entity
   */
  virtual uint8_t GetNumModes (void) const;

  /**
   * Get the WifiMode corresponding to the given MCS index.
   *
   * \param index the index of the MCS
   * \return the WifiMode corresponding to the MCS index
   *
   * This method should be used only for HtPhy and child classes.
   */
  virtual WifiMode GetMcs (uint8_t index) const;
  /**
   * Check if the WifiMode corresponding to the given MCS index is supported.
   *
   * \param index the index of the MCS
   * \return true if the WifiMode corresponding to the MCS index is supported,
   *         false otherwise
   *
   * Will return false for non-MCS modes.
   */
  virtual bool IsMcsSupported (uint8_t index) const;
  /**
   * Check if the WifiModes handled by this PHY are MCSs.
   *
   * \return true if the handled WifiModes are MCSs,
   *         false if they are non-MCS modes
   */
  virtual bool HandlesMcsModes (void) const;

  /**
   * Get the WifiMode for the SIG field specified by the PPDU field.
   *
   * \param field the PPDU field
   * \param txVector the transmission parameters
   *
   * \return the WifiMode used for the SIG field
   *
   * This method is overridden by child classes.
   */
  virtual WifiMode GetSigMode (WifiPpduField field, WifiTxVector txVector) const;

  /**
   * \brief Return a const iterator to the first WifiMode
   *
   * \return a const iterator to the first WifiMode.
   */
  std::list<WifiMode>::const_iterator begin (void) const;
  /**
   * \brief Return a const iterator to past-the-last WifiMode
   *
   * \return a const iterator to past-the-last WifiMode.
   */
  std::list<WifiMode>::const_iterator end (void) const;

  /**
   * Return the field following the provided one.
   *
   * \param currentField the considered PPDU field
   * \param preamble the preamble indicating the PPDU format
   * \return the PPDU field following the reference one
   */
  WifiPpduField GetNextField (WifiPpduField currentField, WifiPreamble preamble) const;

  /**
   * Get the duration of the PPDU field (or group of fields)
   * used by this entity for the given transmission parameters.
   *
   * \param field the PPDU field (or group of fields)
   * \param txVector the transmission parameters
   *
   * \return the duration of the PPDU field
   *
   * This method is overridden by child classes.
   */
  virtual Time GetDuration (WifiPpduField field, WifiTxVector txVector) const;
  /**
   * \param txVector the transmission parameters
   *
   * \return the total duration of the PHY preamble and PHY header.
   */
  Time CalculatePhyPreambleAndHeaderDuration (WifiTxVector txVector) const;

  /**
   * \param size the number of bytes in the packet to send
   * \param txVector the TXVECTOR used for the transmission of this packet
   * \param band the frequency band
   * \param mpdutype the type of the MPDU as defined in WifiPhy::MpduType.
   * \param incFlag this flag is used to indicate that the variables need to be update or not
   * This function is called a couple of times for the same packet so variables should not be increased each time.
   * \param totalAmpduSize the total size of the previously transmitted MPDUs for the concerned A-MPDU.
   * If incFlag is set, this parameter will be updated.
   * \param totalAmpduNumSymbols the number of symbols previously transmitted for the MPDUs in the concerned A-MPDU,
   * used for the computation of the number of symbols needed for the last MPDU.
   * If incFlag is set, this parameter will be updated.
   * \param staId the STA-ID of the PSDU (only used for MU PPDUs)
   *
   * \return the duration of the PSDU
   */
  virtual Time GetPayloadDuration (uint32_t size, WifiTxVector txVector, WifiPhyBand band, MpduType mpdutype,
                                   bool incFlag, uint32_t &totalAmpduSize, double &totalAmpduNumSymbols,
                                   uint16_t staId) const = 0;

  /**
   * A pair containing information on the PHY header chunk, namely
   * the start and stop times of the chunk and the WifiMode used.
   */
  typedef std::pair<std::pair<Time /* start */, Time /* stop */>, WifiMode> PhyHeaderChunkInfo;
  /**
   * A map of PhyHeaderChunkInfo elements per PPDU field.
   * \see PhyHeaderChunkInfo
   */
  typedef std::map<WifiPpduField, PhyHeaderChunkInfo> PhyHeaderSections;
  /**
   * Return a map of PHY header chunk information per PPDU field.
   * This map will contain the PPDU fields that are actually present based
   * on the \p txVector information.
   *
   * \param txVector the transmission parameters
   * \param ppduStart the time at which the PPDU started
   * \return the list of preamble sections
   *
   * \see PhyHeaderSections
   */
  PhyHeaderSections GetPhyHeaderSections (WifiTxVector txVector, Time ppduStart) const;

  /**
   * Build amendment-specific PPDU.
   *
   * \param psdus the PHY payloads (PSDUs)
   * \param txVector the TXVECTOR that was used for the PPDU
   * \param ppduDuration the transmission duration of the PPDU
   * \param band the WifiPhyBand used for the transmission of the PPDU
   * \param uid the unique ID of this PPDU
   *
   * \return the amendment-specific WifiPpdu
   *
   * This method is overridden by child classes to create their
   * corresponding PPDU, e.g., HtPhy creates HtPpdu.
   */
  virtual Ptr<WifiPpdu> BuildPpdu (const WifiConstPsduMap & psdus, WifiTxVector txVector,
                                   Time ppduDuration, WifiPhyBand band, uint64_t uid) const;

  /**
   * Get the duration of the PPDU up to (but excluding) the given field.
   *
   * \param field the considered PPDU field
   * \param txVector the transmission parameters
   * \return the duration from the beginning of the PPDU up to the field
   */
  Time GetDurationUpToField (WifiPpduField field, WifiTxVector txVector) const;
  /**
   * Get the remaining duration of the PPDU after the end of the given field.
   *
   * \param field the considered PPDU field
   * \param ppdu the received PPDU
   * \return the remaining duration of the PPDU after the end of to the field
   */
  Time GetRemainingDurationAfterField (Ptr<const WifiPpdu> ppdu, WifiPpduField field) const;

  /**
   * Get the PSDU addressed to that PHY in a PPDU (useful for MU PPDU).
   *
   * \param ppdu the PPDU to extract the PSDU from
   * \return the PSDU addressed to that PHY
   */
  virtual Ptr<const WifiPsdu> GetAddressedPsduInPpdu (Ptr<const WifiPpdu> ppdu) const;

  /**
   * Start receiving the PHY preamble of a PPDU (i.e. the first bit of the preamble has arrived).
   *
   * This method triggers the start of the preamble detection period (\see
   * StartPreambleDetectionPeriod) if the PHY can process the PPDU.
   *
   * \param ppdu the arriving PPDU
   * \param rxPowersW the receive power in W per band
   * \param rxDuration the duration of the PPDU
   * \param psdFlag the flag indicating the type of Tx PSD to build
   */
  virtual void StartReceivePreamble (Ptr<WifiPpdu> ppdu, RxPowerWattPerChannelBand rxPowersW,
                                     Time rxDuration, TxPsdFlag psdFlag);
  /**
   * Start receiving a given field.
   *
   * This method will call the DoStartReceiveField (which will should
   * be overridden by child classes).
   * EndReceiveField is also scheduled after the duration of the field
   * (except for the special case of preambles \see DoStartReceivePreamble).
   * The PHY is kept in CCA busy during the reception of the field (except for
   * data field which should be in RX).
   *
   * \param field the starting PPDU field
   * \param event the event holding incoming PPDU's information
   */
  void StartReceiveField (WifiPpduField field, Ptr<Event> event);
  /**
   * End receiving a given field.
   *
   * This method will call the DoEndReceiveField (which will should
   * be overridden by child classes) to obtain the outcome of the reception.
   * In case of success, reception of the next field is triggered.
   * In case of failure, the indications in the returned \see PhyFieldRxStatus
   * are performed.
   *
   * \param field the ending PPDU field
   * \param event the event holding incoming PPDU's information
   */
  void EndReceiveField (WifiPpduField field, Ptr<Event> event);

  /**
   * The last symbol of the PPDU has arrived.
   *
   * \param event the event holding incoming PPDU's information
   */
  void EndReceivePayload (Ptr<Event> event);

  /**
   * Reset PHY at the end of the PPDU under reception after it has failed the PHY header.
   *
   * \param event the event holding incoming PPDU's information
   */
  void ResetReceive (Ptr<Event> event);

  /**
   * Cancel and clear all running events.
   */
  virtual void CancelAllEvents (void);
  /**
   * \return \c true if there is no end preamble detection event running, \c false otherwise
   */
  bool NoEndPreambleDetectionEvents (void) const;
  /**
   * Cancel and eventually clear all end preamble detection events.
   *
   * \param clear whether to clear the end preamble detection events' list
   */
  void CancelRunningEndPreambleDetectionEvents (bool clear = false);

  /**
   * Return the STA ID that has been assigned to the station this PHY belongs to.
   * This is typically called for MU PPDUs, in order to pick the correct PSDU.
   *
   * \param ppdu the PPDU for which the STA ID is requested
   * \return the STA ID
   */
  virtual uint16_t GetStaId (const Ptr<const WifiPpdu> ppdu) const;

protected:
  /**
   * A map of PPDU field elements per preamble type.
   * This corresponds to the different PPDU formats introduced by each amendment.
   */
  typedef std::map<WifiPreamble, std::vector<WifiPpduField> > PpduFormats;

  /**
   * Return the PPDU formats of the PHY.
   *
   * This method should be implemented (overridden) by each child
   * class introducing new formats.
   *
   * \return the PPDU formats of the PHY
   */
  virtual const PpduFormats & GetPpduFormats (void) const = 0;

  /**
   * Start receiving a given field, perform amendment-specific actions, and
   * signify if it is supported.
   *
   * \param field the starting PPDU field
   * \param event the event holding incoming PPDU's information
   * \return \c true if the field is supported, \c false otherwise
   */
  virtual bool DoStartReceiveField (WifiPpduField field, Ptr<Event> event);
  /**
   * End receiving a given field, perform amendment-specific actions, and
   * provide the status of the reception.
   *
   * \param field the ending PPDU field
   * \param event the event holding incoming PPDU's information
   * \return status of the reception of the PPDU field
   */
  virtual PhyFieldRxStatus DoEndReceiveField (WifiPpduField field, Ptr<Event> event);

  /**
   * Get the event corresponding to the incoming PPDU.
   *
   * We store all incoming preamble events, perform amendment-specific actions,
   * and a decision is made at the end of the preamble detection window.
   *
   * \param ppdu the incoming PPDU
   * \param rxPowersW the receive power in W per band
   * \return the event holding the incoming PPDU's information
   */
  virtual Ptr<Event> DoGetEvent (Ptr<const WifiPpdu> ppdu, RxPowerWattPerChannelBand rxPowersW);
  /**
   * End receiving the preamble, perform amendment-specific actions, and
   * provide the status of the reception.
   *
   * \param event the event holding incoming PPDU's information
   * \return status of the reception of the preamble
   */
  virtual PhyFieldRxStatus DoEndReceivePreamble (Ptr<Event> event);
  /**
   * Start the preamble detection period.
   *
   * \param event the event holding incoming PPDU's information
   */
  void StartPreambleDetectionPeriod (Ptr<Event> event);
  /**
   * End the preamble detection period.
   *
   * The PHY will focus on the strongest PPDU and drop others.
   * In addition, in case of successful detection, the end of the
   * preamble reception is triggered (\see DoEndReceivePreamble).
   *
   * \param event the event holding incoming PPDU's information
   */
  void EndPreambleDetectionPeriod (Ptr<Event> event);

  /**
   * Start receiving the PSDU (i.e. the first symbol of the PSDU has arrived).
   *
   * \param event the event holding incoming PPDU's information
   */
  void StartReceivePayload (Ptr<Event> event);

  /**
   * Start receiving the PSDU (i.e. the first symbol of the PSDU has arrived)
   * and perform amendment-specific actions.
   *
   * \param event the event holding incoming PPDU's information
   */
  virtual void DoStartReceivePayload (Ptr<Event> event);

  /**
   * Perform amendment-specific actions before resetting PHY at
   * the end of the PPDU under reception after it has failed the PHY header.
   *
   * \param event the event holding incoming PPDU's information
   */
  virtual void DoResetReceive (Ptr<Event> event);

  /**
   * Perform amendment-specific actions before aborting the
   * current reception.
   *
   * \param reason the reason the reception is aborted
   */
  virtual void DoAbortCurrentReception (WifiPhyRxfailureReason reason);

  /**
   * Checks if the signaled configuration (excluding bandwidth)
   * is supported by the PHY.
   *
   * \param ppdu the received PPDU
   * \return \c true if supported, \c false otherwise
   */
  virtual bool IsConfigSupported (Ptr<const WifiPpdu> ppdu) const;

  /**
   * Drop the PPDU and the corresponding preamble detection event, but keep CCA busy
   * state after the completion of the currently processed event.
   *
   * \param ppdu the incoming PPDU
   * \param reason the reason the PPDU is dropped
   * \param endRx the end of the incoming PPDU's reception
   * \param measurementChannelWidth the measurement width (in MHz) to consider for the PPDU
   */
  void DropPreambleEvent (Ptr<const WifiPpdu> ppdu, WifiPhyRxfailureReason reason, Time endRx, uint16_t measurementChannelWidth);

  /**
   * Erase the event corresponding to the PPDU from the list of preamble events,
   * but consider it as noise after the completion of the current event.
   *
   * \param ppdu the incoming PPDU
   * \param rxDuration the duration of the PPDU
   */
  void ErasePreambleEvent (Ptr<const WifiPpdu> ppdu, Time rxDuration);

  /**
   * Get the reception status for the provided MPDU and notify.
   *
   * \param psdu the arriving MPDU formatted as a PSDU
   * \param event the event holding incoming PPDU's information
   * \param staId the station ID of the PSDU (only used for MU)
   * \param relativeMpduStart the relative start time of the MPDU within the A-MPDU. 0 for normal MPDUs
   * \param mpduDuration the duration of the MPDU
   *
   * \return information on MPDU reception: status, signal power (dBm), and noise power (in dBm)
   */
  std::pair<bool, SignalNoiseDbm> GetReceptionStatus (Ptr<const WifiPsdu> psdu,
                                                      Ptr<Event> event, uint16_t staId,
                                                      Time relativeMpduStart,
                                                      Time mpduDuration);
  /**
   * The last symbol of an MPDU in an A-MPDU has arrived.
   *
   * \param event the event holding incoming PPDU's information
   * \param psdu the arriving MPDU formatted as a PSDU containing a normal MPDU
   * \param mpduIndex the index of the MPDU within the A-MPDU
   * \param relativeStart the relative start time of the MPDU within the A-MPDU.
   * \param mpduDuration the duration of the MPDU
   */
  void EndOfMpdu (Ptr<Event> event, Ptr<const WifiPsdu> psdu, size_t mpduIndex, Time relativeStart, Time mpduDuration);

  /**
   * Schedule end of MPDUs events.
   *
   * \param event the event holding incoming PPDU's information
   */
  void ScheduleEndOfMpdus (Ptr<Event> event);

  /**
   * Perform amendment-specific actions at the end of the reception of
   * the payload.
   *
   * \param ppdu the incoming PPDU
   */
  virtual void DoEndReceivePayload (Ptr<const WifiPpdu> ppdu);

  /**
   * Get the channel width and band to use (will be overloaded by child classes).
   *
   * \param txVector the transmission parameters
   * \param staId the station ID of the PSDU
   * \return a pair of channel width (MHz) and band
   */
  virtual std::pair<uint16_t, WifiSpectrumBand> GetChannelWidthAndBand (WifiTxVector txVector, uint16_t staId) const;

  /**
   * Abort the current reception.
   *
   * \param reason the reason the reception is aborted
   */
  void AbortCurrentReception (WifiPhyRxfailureReason reason);

  /**
   * Obtain a random value from the WifiPhy's generator.
   * Wrapper used by child classes.
   *
   * \return a uniform random value
   */
  double GetRandomValue (void) const;
  /**
   * Obtain the SNR and PER of the PPDU field from the WifiPhy's InterferenceHelper class.
   * Wrapper used by child classes.
   *
   * \param field the PPDU field
   * \param event the event holding incoming PPDU's information
   * \return the SNR and PER
   */
  SnrPer GetPhyHeaderSnrPer (WifiPpduField field, Ptr<Event> event) const;
  /**
   * Obtain the received power (W) for a given band.
   * Wrapper used by child classes.
   *
   * \param event the event holding incoming PPDU's information
   * \return the received power (W) for the event over a given band
   */
  double GetRxPowerWForPpdu (Ptr<Event> event) const;
  /**
   * Get the pointer to the current event (stored in WifiPhy).
   * Wrapper used by child classes.
   *
   * \return the pointer to the current event
   */
  Ptr<const Event> GetCurrentEvent (void) const;
  /**
   * Get the map of current preamble events (stored in WifiPhy).
   * Wrapper used by child classes.
   *
   * \return the reference to the map of current preamble events
   */
  const std::map <std::pair<uint64_t, WifiPreamble>, Ptr<Event> > & GetCurrentPreambleEvents (void) const;
  /**
   * Add an entry to the map of current preamble events (stored in WifiPhy).
   * Wrapper used by child classes.
   *
   * \param event the event holding incoming PPDU's information
   */
  void AddPreambleEvent (Ptr<Event> event);

  /**
   * Create an event using WifiPhy's InterferenceHelper class.
   * Wrapper used by child classes.
   *
   * \copydoc InterferenceHelper::Add(Ptr<const WifiPpdu>, WifiTxVector, Time, RxPowerWattPerChannelBand, bool)
   */
  Ptr<Event> CreateInterferenceEvent (Ptr<const WifiPpdu> ppdu, WifiTxVector txVector, Time duration, RxPowerWattPerChannelBand rxPower, bool isStartOfdmaRxing = false);
  /**
   * Update an event in WifiPhy's InterferenceHelper class.
   * Wrapper used by child classes.
   *
   * \copydoc InterferenceHelper::UpdateEvent(Ptr<Event>, RxPowerWattPerChannelBand)
   */
  void UpdateInterferenceEvent (Ptr<Event> event, RxPowerWattPerChannelBand rxPower);
  /**
   * Notify WifiPhy's InterferenceHelper of the end of the reception,
   * clear maps and end of MPDU event, and eventually reset WifiPhy.
   *
   * \param reset whether to reset WifiPhy
   */
  void NotifyInterferenceRxEndAndClear (bool reset);

  Ptr<WifiPhy> m_wifiPhy;          //!< Pointer to the owning WifiPhy
  Ptr<WifiPhyStateHelper> m_state; //!< Pointer to WifiPhyStateHelper of the WifiPhy (to make it reachable for child classes)

  std::list<WifiMode> m_modeList;  //!< the list of supported modes

  std::vector <EventId> m_endPreambleDetectionEvents; //!< the end of preamble detection events
  std::vector <EventId> m_endOfMpduEvents; //!< the end of MPDU events (only used for A-MPDUs)

  std::vector <EventId> m_endRxPayloadEvents; //!< the end of receive events (only one unless UL MU reception)

  /**
   * A pair of a UID and STA_ID
   */
  typedef std::pair <uint64_t /* UID */, uint16_t /* STA-ID */> UidStaIdPair;

  std::map<UidStaIdPair, std::vector<bool> > m_statusPerMpduMap; //!< Map of the current reception status per MPDU that is filled in as long as MPDUs are being processed by the PHY in case of an A-MPDU
  std::map<UidStaIdPair, SignalNoiseDbm> m_signalNoiseMap; //!< Map of the latest signal power and noise power in dBm (noise power includes the noise figure)

}; //class PhyEntity

/**
 * \brief Stream insertion operator.
 *
 * \param os the stream
 * \param action the action to perform in case of failure
 * \returns a reference to the stream
 */
std::ostream& operator<< (std::ostream& os, const PhyEntity::PhyRxFailureAction &action);
/**
 * \brief Stream insertion operator.
 *
 * \param os the stream
 * \param status the status of the reception of a PPDU field
 * \returns a reference to the stream
 */
std::ostream& operator<< (std::ostream& os, const PhyEntity::PhyFieldRxStatus &status);

} //namespace ns3

#endif /* PHY_ENTITY_H */
