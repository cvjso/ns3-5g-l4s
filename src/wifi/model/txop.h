/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#ifndef TXOP_H
#define TXOP_H

#include "ns3/traced-value.h"
#include "wifi-mac-header.h"
#include <memory>
#include <vector>

namespace ns3 {

class Packet;
class ChannelAccessManager;
class MacTxMiddle;
class WifiMode;
class WifiMacQueue;
class WifiMacQueueItem;
class UniformRandomVariable;
class CtrlBAckResponseHeader;
class WifiMac;
enum WifiMacDropReason : uint8_t;  // opaque enum declaration

/**
 * \brief Handle packet fragmentation and retransmissions
 * for data and management frames.
 * \ingroup wifi
 *
 * This class implements the packet fragmentation and
 * retransmission policy for data and management frames.
 * It uses the ns3::ChannelAccessManager helper
 * class to decide when to send a packet.
 * Packets are stored in a ns3::WifiMacQueue
 * until they can be sent.
 *
 * The policy currently implemented uses a simple fragmentation
 * threshold: any packet bigger than this threshold is fragmented
 * in fragments whose size is smaller than the threshold.
 *
 * The retransmission policy is also very simple: every packet is
 * retransmitted until it is either successfully transmitted or
 * it has been retransmitted up until the SSRC or SLRC thresholds.
 *
 * The RTS/CTS policy is similar to the fragmentation policy: when
 * a packet is bigger than a threshold, the RTS/CTS protocol is used.
 */

class Txop : public Object
{
public:
  Txop ();

  /**
   * Constructor
   *
   * \param queue the wifi MAC queue
   */
  Txop (Ptr<WifiMacQueue> queue);

  virtual ~Txop ();

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * typedef for a callback to invoke when an MPDU is dropped.
   */
  typedef Callback <void, WifiMacDropReason, Ptr<const WifiMacQueueItem> > DroppedMpdu;

  /**
   * Enumeration for channel access status
   */
  enum ChannelAccessStatus
  {
    NOT_REQUESTED = 0,
    REQUESTED,
    GRANTED
  };

  /**
   * Check for QoS TXOP.
   *
   * \returns true if QoS TXOP.
   */
  virtual bool IsQosTxop () const;

  /**
   * Set the wifi MAC this Txop is associated to.
   *
   * \param mac associated wifi MAC
   */
  virtual void SetWifiMac (const Ptr<WifiMac> mac);
  /**
   * Set MacTxMiddle this Txop is associated to.
   *
   * \param txMiddle MacTxMiddle to associate.
   */
  void SetTxMiddle (const Ptr<MacTxMiddle> txMiddle);

  /**
   * \param callback the callback to invoke when an MPDU is dropped
   */
  virtual void SetDroppedMpduCallback (DroppedMpdu callback);

  /**
   * Return the packet queue associated with this Txop.
   *
   * \return the associated WifiMacQueue
   */
  Ptr<WifiMacQueue > GetWifiMacQueue () const;

  /**
   * Set the minimum contention window size. For 11be multi-link devices,
   * set the minimum contention window size on the first link.
   *
   * \param minCw the minimum contention window size.
   */
  void SetMinCw (uint32_t minCw);
  /**
   * Set the minimum contention window size for each link.
   * Note that the size of <i>minCws</i> must match the number
   * of links.
   *
   * \param minCws the minimum contention window size values.
   */
  void SetMinCws (std::vector<uint32_t> minCws);
  /**
   * Set the minimum contention window size for the given link.
   *
   * \param minCw the minimum contention window size.
   * \param linkId the ID of the given link
   */
  void SetMinCw (uint32_t minCw, uint8_t linkId);
  /**
   * Set the maximum contention window size. For 11be multi-link devices,
   * set the maximum contention window size on the first link.
   *
   * \param maxCw the maximum contention window size.
   */
  void SetMaxCw (uint32_t maxCw);
  /**
   * Set the maximum contention window size for each link.
   * Note that the size of <i>maxCws</i> must match the number
   * of links.
   *
   * \param maxCws the maximum contention window size values.
   */
  void SetMaxCws (std::vector<uint32_t> maxCws);
  /**
   * Set the maximum contention window size for the given link.
   *
   * \param maxCw the maximum contention window size.
   * \param linkId the ID of the given link
   */
  void SetMaxCw (uint32_t maxCw, uint8_t linkId);
  /**
   * Set the number of slots that make up an AIFS. For 11be multi-link devices,
   * set the number of slots that make up an AIFS on the first link.
   *
   * \param aifsn the number of slots that make up an AIFS.
   */
  void SetAifsn (uint8_t aifsn);
  /**
   * Set the number of slots that make up an AIFS for each link.
   * Note that the size of <i>aifsns</i> must match the number
   * of links.
   *
   * \param aifsns the number of slots that make up an AIFS for each link.
   */
  void SetAifsns (std::vector<uint8_t> aifsns);
  /**
   * Set the number of slots that make up an AIFS for the given link.
   *
   * \param aifsn the number of slots that make up an AIFS.
   * \param linkId the ID of the given link
   */
  void SetAifsn (uint8_t aifsn, uint8_t linkId);
  /**
   * Set the TXOP limit.
   *
   * \param txopLimit the TXOP limit.
   *        Value zero corresponds to default Txop.
   */
  void SetTxopLimit (Time txopLimit);
  /**
   * Return the minimum contention window size. For 11be multi-link devices,
   * return the minimum contention window size on the first link.
   *
   * \return the minimum contention window size.
   */
  uint32_t GetMinCw (void) const;
  /**
   * Return the minimum contention window size for each link.
   *
   * \return the minimum contention window size values.
   */
  std::vector<uint32_t> GetMinCws (void) const;
  /**
   * Return the minimum contention window size for the given link.
   *
   * \param linkId the ID of the given link
   * \return the minimum contention window size.
   */
  virtual uint32_t GetMinCw (uint8_t linkId) const;
  /**
   * Return the maximum contention window size. For 11be multi-link devices,
   * return the maximum contention window size on the first link.
   *
   * \return the maximum contention window size.
   */
  uint32_t GetMaxCw (void) const;
  /**
   * Return the maximum contention window size for each link.
   *
   * \return the maximum contention window size values.
   */
  std::vector<uint32_t> GetMaxCws (void) const;
  /**
   * Return the maximum contention window size for the given link.
   *
   * \param linkId the ID of the given link
   * \return the maximum contention window size.
   */
  virtual uint32_t GetMaxCw (uint8_t linkId) const;
  /**
   * Return the number of slots that make up an AIFS. For 11be multi-link devices,
   * return the number of slots that make up an AIFS on the first link.
   *
   * \return the number of slots that make up an AIFS.
   */
  uint8_t GetAifsn (void) const;
  /**
   * Return the number of slots that make up an AIFS for each link.
   *
   * \return the number of slots that make up an AIFS for each link.
   */
  std::vector<uint8_t> GetAifsns (void) const;
  /**
   * Return the number of slots that make up an AIFS for the given link.
   *
   * \param linkId the ID of the given link
   * \return the number of slots that make up an AIFS.
   */
  virtual uint8_t GetAifsn (uint8_t linkId) const;
  /**
   * Return the TXOP limit.
   *
   * \return the TXOP limit.
   */
  Time GetTxopLimit (void) const;
  /**
   * Update the value of the CW variable for the given link to take into account
   * a transmission success or a transmission abort (stop transmission
   * of a packet after the maximum number of retransmissions has been
   * reached). By default, this resets the CW variable to minCW.
   *
   * \param linkId the ID of the given link
   */
  void ResetCw (uint8_t linkId);
  /**
   * Update the value of the CW variable for the given link to take into account
   * a transmission failure. By default, this triggers a doubling
   * of CW (capped by maxCW).
   *
   * \param linkId the ID of the given link
   */
  void UpdateFailedCw (uint8_t linkId);

  /**
   * Notify that the given link switched to sleep mode.
   *
   * \param linkId the ID of the given link
   */
  virtual void NotifySleep (uint8_t linkId);
  /**
   * When off operation occurs, the queue gets cleaned up.
   */
  virtual void NotifyOff (void);
  /**
   * When wake up operation occurs on a link, channel access on that link
   * will be restarted.
   *
   * \param linkId the ID of the link
   */
  virtual void NotifyWakeUp (uint8_t linkId);
  /**
   * When on operation occurs, channel access will be started.
   */
  virtual void NotifyOn (void);

  /* Event handlers */
  /**
   * \param packet packet to send.
   * \param hdr header of packet to send.
   *
   * Store the packet in the internal queue until it
   * can be sent safely.
   */
  virtual void Queue (Ptr<Packet> packet, const WifiMacHeader &hdr);

  /**
   * Called by the FrameExchangeManager to notify that channel access has
   * been granted on the given link for the given amount of time.
   *
   * \param linkId the ID of the given link
   * \param txopDuration the duration of the TXOP gained (zero for DCF)
   */
  virtual void NotifyChannelAccessed (uint8_t linkId, Time txopDuration = Seconds (0));
  /**
   * Called by the FrameExchangeManager to notify the completion of the transmissions.
   * This method generates a new backoff and restarts access if needed.
   *
   * \param linkId the ID of the link the FrameExchangeManager is operating on
   */
  virtual void NotifyChannelReleased (uint8_t linkId);

  /**
   * Assign a fixed random variable stream number to the random variables
   * used by this model. Return the number of streams (possibly zero) that
   * have been assigned.
   *
   * \param stream first stream index to use.
   *
   * \return the number of stream indices assigned by this model.
   */
  int64_t AssignStreams (int64_t stream);

  /**
   * \param linkId the ID of the given link
   * \return the current channel access status for the given link
   */
  virtual ChannelAccessStatus GetAccessStatus (uint8_t linkId) const;

  /**
   * \param nSlots the number of slots of the backoff.
   * \param linkId the ID of the given link
   *
   * Start a backoff for the given link by initializing the backoff counter to
   * the number of slots specified.
   */
  void StartBackoffNow (uint32_t nSlots, uint8_t linkId);

protected:
  ///< ChannelAccessManager associated class
  friend class ChannelAccessManager;

  void DoDispose (void) override;
  void DoInitialize (void) override;

  /* Txop notifications forwarded here */
  /**
   * Notify that access request has been received for the given link.
   *
   * \param linkId the ID of the given link
   */
  virtual void NotifyAccessRequested (uint8_t linkId);

  /**
   * Check if the Txop has frames to transmit.
   * \return true if the Txop has frames to transmit.
   */
  virtual bool HasFramesToTransmit (void);
  /**
   * Generate a new backoff for the given link now.
   *
   * \param linkId the ID of the given link
   */
  virtual void GenerateBackoff (uint8_t linkId);
  /**
   * Request access from Txop on the given link if needed.
   *
   * \param linkId the ID of the given link
   */
  virtual void StartAccessIfNeeded (uint8_t linkId);
  /**
   * Request access to the ChannelAccessManager associated with the given link
   *
   * \param linkId the ID of the given link
   */
  void RequestAccess (uint8_t linkId);

  /**
   * Get the current value of the CW variable for the given link. The initial
   * value is minCw.
   *
   * \param linkId the ID of the given link
   * \return the current value of the CW variable for the given link
   */
  uint32_t GetCw (uint8_t linkId) const;
  /**
   * Return the current number of backoff slots on the given link.
   *
   * \param linkId the ID of the given link
   * \return the current number of backoff slots
   */
  uint32_t GetBackoffSlots (uint8_t linkId) const;
  /**
   * Return the time when the backoff procedure started on the given link.
   *
   * \param linkId the ID of the given link
   * \return the time when the backoff procedure started
   */
  Time GetBackoffStart (uint8_t linkId) const;
  /**
   * Update backoff slots for the given link that nSlots has passed.
   *
   * \param nSlots the number of slots to decrement
   * \param backoffUpdateBound the time at which backoff should start
   * \param linkId the ID of the given link
   */
  void UpdateBackoffSlotsNow (uint32_t nSlots, Time backoffUpdateBound, uint8_t linkId);

  /**
   * Structure holding information specific to a single link. Here, the meaning of
   * "link" is that of the 11be amendment which introduced multi-link devices. For
   * previous amendments, only one link can be created.
   */
  struct LinkEntity
  {
    /// Destructor (a virtual method is needed to make this struct polymorphic)
    virtual ~LinkEntity () = default;

    uint8_t id {0};                                 //!< Link ID (starting at 0)
    uint32_t backoffSlots {0};                      //!< the number of backoff slots
    Time backoffStart {0};                          /**< the backoffStart variable is used to keep
                                                         track of the time at which a backoff was
                                                         started or the time at which the backoff
                                                         counter was last updated */
    uint32_t cw {0};                                //!< the current contention window
    uint32_t cwMin {0};                             //!< the minimum contention window
    uint32_t cwMax {0};                             //!< the maximum contention window
    uint8_t aifsn {0};                              //!< the AIFSN
    ChannelAccessStatus access {NOT_REQUESTED};     //!< channel access status
  };

  /**
   * Get a reference to the link associated with the given ID.
   *
   * \param linkId the given link ID
   * \return a reference to the link associated with the given ID
   */
  LinkEntity& GetLink (uint8_t linkId) const;
  /**
   * Get the number of links.
   *
   * \return the number of links
   */
  uint8_t GetNLinks (void) const;

  DroppedMpdu m_droppedMpduCallback;                //!< the dropped MPDU callback
  Ptr<WifiMacQueue> m_queue;                        //!< the wifi MAC queue
  Ptr<MacTxMiddle> m_txMiddle;                      //!< the MacTxMiddle
  Ptr<WifiMac> m_mac;                               //!< the wifi MAC
  Ptr<UniformRandomVariable> m_rng;                 //!< the random stream

  Time m_txopLimit;       //!< the TXOP limit time

  /// TracedCallback for backoff trace value typedef
  typedef TracedCallback<uint32_t /* value */, uint8_t /* linkId */> BackoffValueTracedCallback;
  /// TracedCallback for CW trace value typedef
  typedef TracedCallback<uint32_t /* value */, uint8_t /* linkId */> CwValueTracedCallback;

  BackoffValueTracedCallback m_backoffTrace;    //!< backoff trace value
  CwValueTracedCallback m_cwTrace;              //!< CW trace value

private:
  /**
   * Create a LinkEntity object.
   *
   * \return a unique pointer to the created LinkEntity object
   */
  virtual std::unique_ptr<LinkEntity> CreateLinkEntity (void) const;

  std::vector<std::unique_ptr<LinkEntity>> m_links; //!< vector of LinkEntity objects
};

} //namespace ns3

#endif /* TXOP_H */
