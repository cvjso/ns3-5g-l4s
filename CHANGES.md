<!doctype html public "-//w3c//dtd html 4.0 transitional//en">
<html>
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
   <title>ns-3 Change Log</title>
</head>
<body>

<h1>
ns-3: API and model change history</h1>
<!--
This ChangeLog is updated in the reverse order 
with the most recent changes coming first.  Date format:  DD-MM-YYYY
-->
<p>
ns-3 is an evolving system and there will be API or behavioral changes
from time to time.   Users who try to use scripts or models across
versions of ns-3 may encounter problems at compile time, run time, or
may see the simulation output change.  </p>
<p>
We have adopted the development policy that we are going to try to ease
the impact of these changes on users by documenting these changes in a
single place (this file), and not by providing a temporary or permanent
backward-compatibility software layer.  </p>
<p>
A related file is the RELEASE_NOTES.md file in the top level directory.
This file complements RELEASE_NOTES.md by focusing on API and behavioral
changes that users upgrading from one release to the next may encounter.
RELEASE_NOTES.md attempts to comprehensively list all of the changes
that were made.  There is generally some overlap in the information
contained in RELEASE_NOTES.md and this file.  </p>
<p>
The goal is that users who encounter a problem when trying to use older
code with newer code should be able to consult this file to find
guidance as to how to fix the problem.  For instance, if a method name
or signature has changed, it should be stated what the new replacement
name is. </p>
<p>
Note that users who upgrade the simulator across versions, or who work
directly out of the development tree, may find that simulation output
changes even when the compilation doesn't break, such as when a
simulator default value is changed.  Therefore, it is good practice for
_anyone_ using code across multiple ns-3 releases to consult this file,
as well as the RELEASE_NOTES.md, to understand what has changed over time.
</p>
<p>
This file is a best-effort approach to solving this issue; we will do
our best but can guarantee that there will be things that fall through
the cracks, unfortunately.  If you, as a user, can suggest improvements
to this file based on your experience, please contribute a patch or drop
us a note on ns-developers mailing list.</p>

<hr>
<h1>Changes from ns-3.35 to ns-3.36</h1>
<h2>New API:</h2>
<ul>
<li>The helpers of the NetDevices supporting flow control (PointToPointHelper, CsmaHelper, SimpleNetDeviceHelper, WifiHelper) now provide a <b>DisableFlowControl</b> method to disable flow control. If flow control is disabled, the Traffic Control layer forwards packets down to the NetDevice even if there is no room for them in the NetDevice queue(s)</li>
<li>Added a new trace source <b>TcDrop</b> in TrafficControlLayer for tracing packets that have been dropped because no queue disc is installed on the device, the device supports flow control and the device queue is full.</li>
<li>Added a new class <b>PhasedArraySpectrumPropagationLossModel</b>, and its <b>DoCalcRxPowerSpectralDensity</b> function has two additional parameters: TX and RX antenna arrays. Should be inherited by models that need to know antenna arrays in order to calculate RX PSD.</li>
<li>It is now possible to detach a SpectrumPhy object from a SpectrumChannel by calling SpectrumChannel::RemoveRx ().</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li>internet: Support for Network Simulation Cradle (NSC) TCP has been removed.</li>
<li>fd-net-device: Support for PlanetLabFdNetDeviceHelper has been removed.</li>
<li><b>ThreeGppSpectrumPropagationLossModel</b> now inherits <b>PhasedArraySpectrumPropagationLossModel</b>. The modules that use <b>ThreeGppSpectrumPropagationLossModel</b> should implement <b>SpectrumPhy::GetAntenna</b> that will return the instance of <b>PhasedArrayModel</b>.</li>
<li><b>AddDevice</b> function is removed from <b>ThreeGppSpectrumPropagationLossModel</b> to support multiple arrays per device.</li>
<li><b>SpectrumPhy</b> function <b>GetRxAntenna</b> is renamed to <b>GetAntenna</b>, and its return value is changed to <b>Ptr<Object></b> instead of <b>Ptr<AntennaModel></b> to support also <b>PhasedArrayModel</b> type of antenna.</li>
<li><b>vScatt</b> attribute moved from ThreeGppSpectrumPropagationLossModel to ThreeGppChannelModel.</li>
<li><b>ChannelCondition::IsEqual</b> now has LOS and O2I parameters instead of a pointer to ChannelCondition.</li>
<li>tcp: <b>TcpWestwood::EstimatedBW</b> trace source changed from <b>TracedValueCallback::Double</b> to <b>TracedValueCallback::DataRate</b>.</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li>G++ version 8 is now the minimum G++ version supported.</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li>Wi-Fi: The default Wi-Fi standard is changed from 802.11a to 802.11ax, and the default rate control is changed from ArfWifiManager to IdealWifiManager.
<li>Wi-Fi: EDCAFs (QosTxop objects) are no longer installed on non-QoS STAs and DCF (Txop object) is no longer installed on QoS STAs.</li>
<li>Wi-Fi: Management frames (Probe Request/Response, Association Request/Response) are sent by QoS STAs according to the 802.11 specs.</li>
<li>The <b>Frequency</b>, <b>ChannelNumber</b>, <b>ChannelWidth</b> and <b>Primary20MHzIndex</b>
attributes of <b>WifiPhy</b> can now only be used to get the corresponding values. Channel settings
can be now configured through the <b>ChannelSettings</b> attribute. See the wifi model documentation
for information on how to set this new attribute.</li>
<li>UE handover now works with and without enabled CA (carrier aggregation) in inter-eNB, intra-eNB, inter-frequency and intra-frequency scenarios. Previously only inter-eNB intra-frequency handover was supported and only in non-CA scenarios. </li>
<li>NixVectorRouting: <b>NixVectorRouting</b> can now better cope with topology changes. In-flight packets are not anymore causing crashes, and
the path is dynamically rebuilt by intermediate routers (this happens only to packets in-flight during the topology change).</li>
<li>Mesh (Wi-Fi) forwarding hops now have a configurable random variable-based forwarding delay model, with a default mean of 350 us.</li>.
</ul>

<hr>
<h1>Changes from ns-3.34 to ns-3.35</h1>
<h2>New API:</h2>
<ul>
<li>In class <b>Ipv6Header</b>, new functions SetSource (), SetDestination (), GetSource () and GetDestination () are added, consistent with <b>Ipv4Header</b>. The existing functions had "Address" suffix in each of the function names, and are are deprecated now.</li>
<li>In class <b>Ipv4InterfaceAddress</b>, new functions SetAddress () and GetAddress () are added, corresponding to SetLocal () and GetLocal () respectively. This is done to keep consistency with <b>Ipv4InterfaceAddress</b>.</li>
<li>With the new support for IPv6 Nix-Vector routing, we have all the new APIs corresponding to IPv4 Nix-Vector routing. Specific to the user, there is an Ipv6NixVectorHelper class which can be set in the InternetStackHelper, and works similar to Ipv4NixVectorHelper.</li>
<li>In class <b>Ipv4InterfaceAddress</b>, a new function IsInSameSubnet () is added to check if both the IPv4 addresses are in the same subnet. Also, it is consistent with <b>Ipv6InterfaceAddress::IsInSameSubnet ()</b>.</li>
<li>In class <b>ConfigStore</b>, a new Attribue <b>SaveDeprecated</b> allows to not save DEPRECATED Attributes. The default value is <b>false</b> (save DEPRECATED Attributes).</li>
<li>In class <b>TracedCallback</b>, a new function <b>IsEmpty</b> allows to know if the TracedCallback will call any callback.</li>
<li>A new specialization of std::hash for Ptr allows one to use Ptrs as keys in unordered_map and unordered_set containers.</li>
<li>A new <b>GroupMobilityHelper</b> mobility helper has been added to ease the configuration of group mobility (a form of hierarchical mobility in which multiple child mobility models move with reference to an underlying parent mobility model).  New example programs and animation scripts are also added to both the buildings and mobility modules.</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li>In class <b>Ipv6Header</b>, the functions SetSourceAddress (), SetDestinationAddress (), GetSourceAddress () and GetDestinationAddress () are deprecated. New corresponding functions are added by removing the "Address" suffix. This change is made for having consistency with <b>Ipv4Header</b>.</li>
<li><b>ipv4-nix-vector-helper.h</b> and <b>ipv4-nix-vector-routing.h</b> have been deprecated in favour of <b>nix-vector-helper.h</b> and <b>nix-vector-routing.h</b> respectively.</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li>The default C++ standard is now C++17.</li>
<li>The minimum compiler versions have been raised to g++-7 and clang-10 (Linux) and Xcode 11 (macOS).</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li>Nix-Vector routing supports topologies with multiple WiFi networks using the same WiFi channel object.</li>
<li>ConfigStore no longer saves OBSOLETE attributes.</li>
<li>The <b>Ipv4L3Protocol</b> Duplicate detection now accounts for transmitted packets, so a transmitting multicast node will not forward its own packets.</li>
<li>Wi-Fi: A-MSDU aggregation now implies that constituent MSDUs are immediately dequeued
from the EDCA queue and replaced by an MPDU containing the A-MSDU. Thus, aggregating N
MSDUs triggers N dequeue operations and 1 enqueue operation on the EDCA queue.</li>
<li>Wi-Fi: MPDUs being passed to the PHY layer for transmission are not dequeued, but
are kept in the EDCA queue until they are acknowledged or discarded. Consequently, the
BlockAckManager retransmit queue has been removed.</li>
</ul>

<hr>
<h1>Changes from ns-3.33 to ns-3.34</h1>
<h2>New features and API:</h2>
<ul>
<li>Support for Wi-Fi <b>802.11ax downlink and uplink OFDMA</b>, including multi-user OFDMA and a <b>round-robin multi-user scheduler</b>.</li>
<li><b>FqCobalt</b> queue disc with L4S features and set associative hash.</li>
<li><b>FqPIE</b> queue disc with L4S mode</li>
<li><b>ThompsonSamplingWifiManager</b> Wi-Fi rate control algorithm.</li>
<li>New <b>PhasedArrayModel</b>, providing a flexible interface for modeling a number of Phase Antenna Array (PAA) models.</li>
<li>Added the ability to configure the <b>Wi-Fi primary 20 MHz channel</b> for 802.11 devices operating on channels of width greater than 20 MHz.</li>
<li>A <b>TCP BBRv1</b> congestion control model.</li>
<li><b>Improved support for bit fields</b> in header serialization/deserialization.</li>
<li>Support for <b>IPv6 stateless address auto-configuration (SLAAC)</b>.</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li>The <b>WifiAckPolicySelector</b> class has been replaced by the <b>WifiAckManager</b> class. Correspondingly, the ConstantWifiAckPolicySelector has been replaced by the WifiDefaultAckManager class. A new WifiProtectionManager abstract base class and WifiDefaultProtectionManager concrete class have been added to implement different protection policies.</li>
<li>The class <b>ThreeGppAntennaArrayModel</b> has been replaced by <b>UniformPlanarArray</b>, extending the PhasedArrayModel interface.</li>
<li>The <b>Angles struct</b> is now a class, with robust setters and getters (public struct variables phi and theta are now private class variables m_azimuth and m_inclination), overloaded operator&lt;&lt; and operator&gt;&gt; and a number of utilities.</li>
<li><b>AntennaModel</b> child classes have been extended to produce 3D radiation patterns. Attributes such as Beamwidth have thus been separated into Vertical/HorizontalBeamwidth.</li>
<li>The attribute <b>UseVhtOnly</b> in <b>MinstrelHtWifiManager</b> has been replaced by a new attribute called <b>UseLatestAmendmentOnly</b>.
<li> The wifi module has <b>removed HT Greenfield support, Holland (802.11a-like) PHY configuration, and Point Coordination Function (PCF)</b></li>
<li> The wifi ErrorRateModel API has been extended to support <b>link-to-system models</b>.
<li> <b>Nix-Vector routing</b> supports multiple interface addresses and can print out routing paths</b>.
<li>The <b>TxOkHeader and TxErrHeader trace sources</b> of RegularWifiMac have been obsoleted and replaced by trace sources that better capture the result of a transmission: AckedMpdu (fired when an MPDU is successfully acknowledged, via either a Normal Ack or a Block Ack), NAckedMpdu (fired when an MPDU is negatively acknowledged via a Block Ack), DroppedMpdu (fired when an MPDU is dropped), MpduResponseTimeout (fired when a CTS is missing after an RTS or a Normal Ack is missing after an MPDU) and PsduResponseTimeout (fired when a BlockAck is missing after an A-MPDU or a BlockAckReq).</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li> The handling of <b>Boost library/header dependencies</b> has been improved.</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li>The default <b>TCP congestion control</b> has been changed from NewReno to CUBIC.</li>
<li>The <b>PHY layer of the wifi module</b> has been refactored: the amendment-specific logic has been ported to <b>PhyEntity</b> classes and <b>WifiPpdu</b> classes.</li>
<li>The <b>MAC layer of the wifi module</b> has been refactored. The MacLow class has been replaced by a hierarchy of FrameExchangeManager classes, each adding support for the frame exchange sequences introduced by a given amendment.</li>
<li>The <b>wifi BCC AWGN error rate tables</b> have been aligned with the ones provided by MATLAB and users may note a few dB difference when using BCC at high SNR and high MCS.</li>
<li><b>ThreeGppChannelModel has been fixed</b>: cluster and sub-cluster angles could have been generated with inclination angles outside the inclination range [0, pi], and have now been constrained to the correct range.</li>
<li>The <b>LTE RLC Acknowledged Mode (AM) transmit buffer</b> is now limited by default to a size of (1024 * 10) bytes.  Configuration of unlimited behavior can still be made by passing the value of zero to the new attribute <b>MaxTxBufferSize</b>.</li>
</ul>

<hr>
<h1>Changes from ns-3.32 to ns-3.33</h1>
<h2>New API:</h2>
<ul>
<li>A model for <b>TCP CUBIC</b> (RFC 8312) has been added.</li>
<li>New <b>channel models based on 3GPP TR 37.885</b> have been added to support vehicular simulations.</li>
<li><b>Time::RoundTo (unit)</b> allows time to be rounded to the nearest integer multiple of unit</li>
<li><b>UdpClient</b> now can report both transmitted and received bytes.</li>
<li>A new <b>MPI Enable()</b> variant was introduced that takes a user-supplied MPI_Communicator, allowing for partitioning of the MPI processes.</li>
<li>A <b>Length</b> class has been introduced to allow users to replace the use of raw numbers (ints, doubles) that have implicit lengths with a class that represents lengths with an explicit unit.</li>
<li>A flexible <b>CsvReader</b> class has been introduced to allow users to read in csv- or tab-delimited data.</li>
<li>The <b>ListPositionAllocator</b> can now input positions from a csv file.</li>
<li>A new trace source for DCTCP alpha value has been added to <b>TcpDctcp</b>.</li>
<li>A new <b>TableBasedErrorRateModel</b> has been added for Wi-Fi, and the default values are aligned with link-simulation results from MATLAB WLAN Toolbox and IEEE 802.11 TGn.
</li>
<li>A new <b>LdpcSupported</b> attribute has been added for Wi-Fi in <b>HtConfiguration</b>, in order to select LDPC FEC encoding instead of the default BCC FEC encoding.
</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li> The signature of <b>WifiPhy::PsduTxBeginCallback</b> and <b>WifiPhy::PhyTxPsduBegin</b> have been changed to take a map of PSDUs instead of a single PSDU
in order to support multi-users (MU) transmissions.
</li>
<li> The wifi trace <b>WifiPhy::PhyRxBegin</b> has been extended to report the received power for every band.
</li>
<li> The wifi trace <b>WifiPhy::PhyRxBegin</b> has been extended to report the received power for every band.
</li>
<li>New attributes <b>SpectrumWifiPhy::TxMaskInnerBandMinimumRejection</b>, <b>SpectrumWifiPhy::TxMaskOuterBandMinimumRejection</b> and <b>SpectrumWifiPhy::TxMaskOuterBandMaximumRejection</b> have been added to configure the OFDM transmit masks.
</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li>Waf has been upgraded to git development version waf-2.0.21-6-g60e3f5f4</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li>The <b>default Wi-Fi ErrorRateModel</b> for the 802.11n/ac/ax standards has been changed from the NistErrorRateModel to a new TableBasedErrorRateModel.  Users may experience a shift in Wi-Fi link range due to the new default error model, as <b>the new model is more optimistic</b> (the PER for a given MCS will degrade at a lower SNR value). The Wi-Fi module documentation provides plots that compare the performance of the NIST and new table-based model.</li>
<li>The default value of the <b>BerThreshold</b> attribute in <b>IdealWifiManager</b> was changed from 1e-5 to 1e-6, so as to correct behavior with high order MCS.</li>
<li> <b>Time values that are created from an int64x64_t value</b> are now rounded to the nearest integer multiple of the unit, rather than truncated.  Issue #265 in the GitLab.com tracker describes the behavior that was fixed.  Some Time values that rely on this conversion may have changed due to this fix.</li>
<li> TCP now implements the Linux-like <b>congestion window reduced (CWR)</b> state when explicit congestion notification (ECN) is enabled.</li>
<li> <b>TcpDctcp</b> now inherits from <b>TcpLinuxReno</b>, making its congestion avoidance track more closely to that of Linux.</li>
</ul>

<hr>
<h1>Changes from ns-3.31 to ns-3.32</h1>
<h2>New API:</h2>
<ul>
<li>A new TCP congestion control, <b>TcpLinuxReno</b>, has been added.</li>
<li>Added, to <b>PIE queue disc</b>, <b>queue delay calculation using timestamp</b> feature (Linux default behavior), <b>cap drop adjustment</b> feature (Section 5.5 of RFC 8033), <b>ECN</b> (Section 5.1 of RFC 8033) and <b>derandomization</b> feature (Section 5.4 of RFC 8033).</li>
<li>Added <b>L4S Mode</b> to FqCoDel and CoDel queue discs</li>
<li> A model for <b>dynamic pacing</b> has been added to TCP.</li>
<li>Added <b>Active/Inactive feature</b> to PIE queue disc</li>
<li>Added <b>netmap</b> and <b>DPDK</b> emulation device variants</li>
<li>Added capability to configure <b>STL pair and containers as attributes</b></li>
<li> Added <b>CartesianToGeographic</b> coordinate conversion capability</li>
<li> Added <b>LollipopCounter</b>, a sequence number counter type</li>
<li> Added <b>6 GHz band</b> support for Wi-Fi 802.11ax</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li>The <b>Sifs</b>, <b>Slot</b> and <b>Pifs</b> attributes have been moved from <b>WifiMac</b> to <b>WifiPhy</b> to better reflect that they are PHY characteristics, to decouple the MAC configuration from the PHY configuration and to ease the support for future standards.</li>
<li>The Histogram class was moved from the flow-monitor module to the stats
module to make it more easily accessed.  If you previously used Histogram by
by including flow-monitor.h you will need to change that to stats-module.h.
</li>
<li>The <b>WifiHelper::SetStandard (WifiPhyStandard standard)</b> method no
longer takes a WifiPhyStandard enum, but instead takes a similarly named 
WifiStandard enum.  If before you specified a value such as WIFI_PHY_STANDARD_xxx, now you must specify WIFI_STANDARD_xxx.
</li>
<li> The <b>YansWifiPhyHelper::Default</b> and <b>SpectrumWifiPhyHelper::Default</b> methods have been removed; the default constructors may instead by used.</li>
<li> <b>PIE</b> queue disc now uses <b>Timestamp</b> for queue delay calculation as default instead of <b>Dequeue Rate Estimator</b></li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li>Added "--enable-asserts" and "--enable-logs" to waf configure, to selectively enable asserts and/or logs in release and optimized builds.</li>
<li>A build version reporting system has been added by extracting data from the 
local git repository (or a standalone file if a git repository is not present).  </li>
<li>Added support for EditorConfig</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li>Support for <b>RIFS</b> has been dropped from wifi. RIFS has been obsoleted by the 802.11 standard and support for it was not implemented according to the standard.</li>
<li>The default loss recovery algorithm for TCP has been changed from Classic Recovery to Proportional Rate Reduction (PRR).</li>
<li>The behavior of <b>TcpPrrRecovery</b> algorithm was aligned to that of Linux.</li>
<li> <b>PIE</b> queue disc now uses <b>Timestamp</b> for queue delay calculation as default instead of <b>Dequeue Rate Estimator</b></li>
<li>TCP pacing, when enabled, now adjusts the rate dynamically based on the window size, rather than just enforcing a constant rate.</li>
<li>WifiPhy forwards up MPDUs from an A-MPDU under reception as long as they arrive at the PHY, instead of forwarding up the whole A-MPDU once its reception is completed.</li>
<li>The ns-3 TCP model was changed to set the initial congestion window to 10 segments instead of 1 segment (to align with default Linux configuration).</li>
</ul>

<hr>
<h1>Changes from ns-3.30 to ns-3.31</h1>
<h2>New API:</h2>
<ul>
<li> A <b>TCP DCTCP</b> model has been added.</li>
<li> <b>3GPP TR 38.901</b> pathloss, channel condition, antenna array, and fast fading models have been added.</li>
<li> New <b>...FailSafe ()</b> variants of the <b> Config </b> and <b>Config::MatchContainer</b> functions which set Attributes or connect TraceSources.  These all return a boolean indicating if any attributes could be set (or trace sources connected).  These are useful if you are not sure that the requested objects exist, for example in AnimationInterface.</li>
<li> New attributes for <b> Ipv4L3Protocol</b> have been added to enable RFC 6621-based duplicate packet detection (DPD) (<b>EnableDuplicatePacketDetection</b>) and to control the cache expiration time (<b>DuplicateExpire</b>).</li>
<li><b> MakeConsistent </b> method of <b> BuildingsHelper </b> class is 
deprecated and moved to <b> MobilityBuildingInfo </b> class. <b> DoInitialize </b> 
method of the <b> MobilityBuildingInfo </b> class would be responsible for making 
the mobility model of a node consistent at the beginning of a simulation. 
Therefore, there is no need for an explicit call to <b> MakeConsistent </b> in a simulation script.</li>
<li> The <b> IsInside </b> method of <b> MobilityBuildingInfo </b> class is extended 
to make the mobility model of a moving node consistent.</li>
<li> The <b> IsOutside </b> method of <b> MobilityBuildingInfo </b> class is 
deprecated. The <b> IsInside </b> method should be use to check the position of a node.</li>
<li>A new abstract base class, <b>WifiAckPolicySelector</b>, is introduced to implement
different techniques for selecting the acknowledgment policy for PSDUs containing
QoS Data frames. Wifi, mesh and wave helpers provide a SetAckPolicySelectorForAc
method to configure a specific ack policy selector for a given Access Category.</li>
<ul>
<li>The default ack policy selector is named <b>ConstantWifiAckPolicySelector</b>, which
allows to choose between Block Ack policy and Implicit Block Ack Request policy and
allows to request an acknowledgment after a configurable number of MPDUs have been
transmitted.</li>
</ul>
<li>The <b>MaxSize</b> attribute is removed from the <b>QueueBase</b> base class and moved to subclasses. A new MaxSize attribute is therefore added to the DropTailQueue class, while the MaxQueueSize attribute of the WifiMacQueue class is renamed as MaxSize for API consistency.</li>
<li> Two new <b>Application sequence number and timestamp</b> variants have been added, to support packet delivery tracing.
<ul>
<li> A new sequence and timestamp header variant for applications has been added.  The <b>SeqTsEchoHeader</b> contains an additional timestamp field for use in echoing a timestamp back to a sender.</li>
<li> TCP-based applications (OnOffApplication, BulkSendApplication, and PacketSink) support a new header, <b>SeqTsSizeHeader</b>, to convey sequence number, timestamp, and size data.  Use is controlled by the "EnableSeqTsSizeHeader" attribute.</li>
</ul>
<li>Added a new trace source <b>PhyRxPayloadBegin</b> in WifiPhy for tracing begin of PSDU reception.</li>
<li>Added the class <b>RandomWalk2dOutdoorMobilityModel</b> that models a random walk which does not enter any building.</li>
<li>Added support for the <b>Cake set-associative hash</b> in the FqCoDel queue disc</li>
<li>Added support for <b>ECN marking for CoDel and FqCoDel</b> queue discs</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li> The API for <b>enabling and disabling ECN</b> in TCP sockets has been refactored.</li>
<li> The <b>LTE HARQ</b> related methods in LteEnbPhy and LteUePhy have been renamed, and the LteHelper updated.</li>
<li> Previously the <b>Config::Connect</b> and <b>Config::Set</b> families of functions would fail silently if the attribute or trace source didn't exist on the path given (typically due to spelling errors). Now those functions will throw a fatal error.  If you need the old behavior use the new  <b>...FailSafe ()</b> variants.</li>
<li>The internal TCP API for <b>TcpCongestionOps</b> has been extended to support the <b>CongControl</b> method to allow for delivery rate estimation feedback to the congestion control mechanism.</li>
<li>Functions <b>LteEnbPhy::ReceiveUlHarqFeedback</b> and <b>LteUePhy::ReceiveLteDlHarqFeedback</b> are renamed to <b>LteEnbPhy::ReportUlHarqFeedback</b> and <b>LteUePhy::EnqueueDlHarqFeedback</b>, respectively to avoid confusion about their functionality. <b>LteHelper</b> is updated accordingly.</li>
<li>Now on, instead of <b>uint8_t</b>, <b>uint16_t</b> would be used to store a bandwidth value in LTE.</li>
<li>The preferred way to declare instances of <b>CommandLine</b> is now through a macro: <b>COMMANDLINE (cmd)</b>.  This enables us to add the <b>CommandLine::Usage()</b> message to the Doxygen for the program.</li>
<li>New <b>...FailSafe ()</b> variants of the <b> Config </b> is used to connect PDCP TraceSources of eNB and UE in <b>RadioBearerStatsConnector</b> class. It is required for the simulations using RLC SM where PDCP objects are not created for data radio bearers.</li>
<li><b>T310</b> timer in <b>LteUeRrc</b> class is stopped if the UE receives <b>RRCConnectionReconfiguration</b> including the <b>mobilityControlInfo</b>. This change is introduced following the 3GPP standard TS36331 sec 5.3.5.4.</li>
<li>The wifi <b>High Latency tags</b> have been removed.  The only rate manager (Onoe) that was making use of them has been refactored.</li>
<li>The wifi <b>MIMO diversity model</b> has been changed to better fit with MRC theory for AWGN channels when STBC is not used (since STBC is currently not supported).</li>
<li> The <b>BuildingsHelper::MakeMobilityModelConsistent()</b> method is deprecated in favor of MobilityBuildingInfo::MakeConsistent</li>
<li> The <b>MobilityBuildingInfo::IsOutdoor ()</b> method is deprecated; use the result of IsIndoor() method instead</li>
<li> IsEqual() methods of class <b>Ipv4Address, Ipv4Mask, Ipv6Address, and Ipv6Prefix</b> are deprecated.</li>
<li> The API around the <b>wifi Txop class</b> was refactored.</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li>The <b>--lcov-report</b> option to Waf was fixed, and a new <b>--lcov-zerocounters</b> option was added to improve support for lcov.</li>
<li>Python bindings were enabled for <b>netanim</b>.</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li> The <b>EmpiricalRandomVariable</b> no longer linearly interpolates between values by default, but instead will default to treating the CDF as a histogram and return one of the specific inputs.  The previous interpolation mode can be configured by an attribute.</li>
<li> (as reported above) previously the <b>Config::Connect</b> and <b>Config::Set</b> families of functions would fail silently if the attribute or trace source didn't exist on the path given (typically due to spelling errors). Now those functions will throw a fatal error.  If you need the old behavior use the new  <b>...FailSafe ()</b> variants.</li>
<li> Attempting to deserialize an enum name which wasn't registered with <b>MakeEnumChecker</b> now causes a fatal error, rather failing silently. (This can be triggered by setting an enum Attribute from a StringValue.)</li>
<li> As a result of the above API changes in <b> MobilityBuildingInfo </b> 
and <b> BuildingsHelper </b> classes, a building aware pathloss models, e.g., 
<b> HybridBuildingsPropagationLossModel </b> is now able to accurately compute 
the pathloss for a node moving in and out of buildings in a simulation. See <a href=https://gitlab.com/nsnam/ns-3-dev/issues/80>issue 80</a> 
for discussion.</li>
<li> The implementation of the <b>Wi-Fi channel access</b> functions has been improved
to make them more conformant to the IEEE 802.11-2016 standard. Concerning the DCF,
the backoff procedure is no longer invoked when a packet is queued for transmission
and the medium has not been idle for a DIFS, but it is invoked if the medium is busy
or does not remain idle for a DIFS after the packet has been queued. Concerning the
EDCAF, tranmissions are now correctly aligned at slot boundaries.</li>
<li> Various wifi physical layer behavior around channel occupancy calculation, phy state calculation, and handling different channel widths has been updated.</li>
</ul>

<hr>
<h1>Changes from ns-3.29 to ns-3.30</h1>
<h2>New API:</h2>
<ul>
<li>Added the attribute <b>Release</b> to the class <b>EpsBearer</b>, to select the release (e.g., release 15)</li>
<li>The attributes <b>RegularWifiMac::HtSupported</b>, <b>RegularWifiMac::VhtSupported</b>, <b>RegularWifiMac::HeSupported</b>, <b>RegularWifiMac::RifsSupported</b>, <b>WifiPhy::ShortGuardEnabled</b>, <b>WifiPhy::GuardInterval</b> and <b>WifiPhy::GreenfieldEnabled</b> have been deprecated. Instead, it is advised to use <b>WifiNetDevice::HtConfiguration</b>, <b>WifiNetDevice::VhtConfiguration</b> and <b>WifiNetDevice::HeConfiguration</b>.</li>
<li>The attributes <b>{Ht,Vht,He}Configuration::{Vo,Vi,Be,Bk}MaxAmsduSize</b> and <b>{Ht,Vht,He}Configuration::{Vo,Vi,Be,Bk}MaxAmpduSize</b> have been removed. Instead, it is necessary to use <b>RegularWifiMac::{VO, VI, BE, BK}_MaxAmsduSize</b> and <b>RegularWifiMac::{VO, VI, BE, BK}_MaxAmpduSize</b>.</li>
<li>A new attribute <b>WifiPhy::PostReceptionErrorModel</b> has been added to force specific packet drops.</li>
<li>A new attribute <b>WifiPhy::PreambleDetectionModel</b> has been added to decide whether PHY preambles are successfully detected.</li>
<li>New attributes <b>QosTxop::AddBaResponseTimeout</b> and <b>QosTxop::FailedAddBaTimeout</b> have been added to set the timeout to wait for an ADDBA response after the ACK to the ADDBA request is received and to set the timeout after a failed BA agreement, respectively.</li>
<li>A new attribute <b>QosTxop::UseExpliciteBarAfterMissedBlockAck</b> has been added to specify whether explicit Block Ack Request should be sent upon missed Block Ack Response.</li>
<li>Added a new trace source <b>EndOfHePreamble</b> in WifiPhy for tracing end of preamble (after training fields) for received 802.11ax packets.</li>
<li>Added a new helper method to SpectrumWifiPhyHelper and YansWifiPhyHelper to set the <b>frame capture model</b>.</li>
<li>Added a new helper method to SpectrumWifiPhyHelper and YansWifiPhyHelper to set the <b>preamble detection model</b>.</li>
<li>Added a new helper method to WifiPhyHelper to disable the preamble detection model.</li>
<li>Added a method to ObjectFactory to check whether a TypeId has been configured on the factory.</li>
<li>Added a new helper method to WifiHelper to set the <b>802.11ax OBSS PD spatial reuse algorithm</b>.</li>
<li>Added the <b>Cobalt queuing discipline</b>.</li>
<li>Added <b>Simulator::GetEventCount ()</b> to return the number of events executed.</li> 
<li>Added <b>ShowProgress</b> object to display simulation progress statistics.</li>
<li>Add option to disable explicit Block Ack Request when a Block Ack Response is missed.</li>
<li>Add API to be able to tag a subset of bytes in an ns3::Packet.</li>
<li>New LTE helper API has been added to allow users to configure LTE backhaul links with any link technology, not just point-to-point links.</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
  <li>
    Added the possibility of setting the z coordinate for many position-allocation classes: <b>GridPositionAllocator, RandomRectanglePositionAllocator, RandomDiscPositionAllocator, UniformDiscPositionAllocator</b>.
  </li>
  <li>
    The WifiPhy attribute <b>CcaMode1Threshold</b> has been renamed to <b>CcaEdThreshold</b>, 
    and the WifiPhy attribute <b>EnergyDetectionThreshold</b> has been replaced by a new attribute called <b>RxSensitivity</b>.
  </li>
  <li>
    It is now possible to know the size of the SpectrumValue underlying std::vector, as well as
    accessing read-only every element of it.
  </li>
  <li>
    The <b>GetClosestSide</b> method of the Rectangle class returns the correct closest side also for positions outside the rectangle.
  </li>
  <li> The trace sources <b>BackoffTrace</b> and <b>CwTrace</b> were moved from class QosTxop to base class Txop, allowing these values to be traced for DCF operation.  In addition, the trace signature for BackoffTrace was changed from TracedValue to TracedCallback (callback taking one argument instead of two).  Most users of CwTrace for QosTxop configurations will not need to change existing programs, but users of BackoffTrace will need to adjust the callback signature to match.
  </li>
  <li> New trace sources, namely <b>DrbCreated, Srb1Created and DrbCreated</b> have beed implemented in LteEnbRrc and LteUeRrc classes repectively. These new traces are used to improve the connection of the RLC and PDCP stats in the RadioBearerStatsConnector API.
  </li>
  <li> <b>TraceFadingLossModel</b> has been moved from lte to spectrum module.
  </li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li><b>ns-3 now only supports Python 3</b>.  Use of Python 2 can be forced using the --with-python option provided to './waf configure', and may still work for many cases, but is no longer supported.  Waf does not default to Python 3 but the ns-3 wscript will default the build to Python 3.
  </li>
  <li>Waf upgraded from 2.0.9 to 2.0.18.
  </li>
  <li> Options to run a program through Waf without invoking a project rebuild have been added.  The command './waf --run-no-build <program-name>' parallels the behavior of './waf --run <program-name>' and, likewise, the command './waf --pyrun-no-build' parallels the behavior of './waf --pyrun <program-name>'.
  </li>
</ul>
<h2>Changed behavior:</h2>
<ul>
  <li>The wifi ADDBA handshake process is now protected with the use of two timeouts who makes sure we do not end up in a blocked situation. If the handshake process is not established, packets that are in the queue are sent as normal MPDUs. Once handshake is successfully established, A-MPDUs can be transmitted.</li>
  <li> In the wifi module, the default value of the <b>Margin</b> attribute in SimpleFrameCaptureModel was changed from 10 to 5 dB.</li>
  <li> A <b>ThresholdPreambleDetectionModel</b> is added by default to the WifiPhy.  Using default values, this model will discard frames that fall below either -82 dBm RSSI or below 4 dB SNR.  Users may notice that weak wifi signals that were successfully received based on the error model alone (in previous ns-3 releases) are no longer received.  Previous behavior can be obtained by lowering both threshold values or by removing the preamble detection model (via WifiPhyHelper::DisablePreambleDetectionModel()).</li>
  <li>The PHY model for Wi-Fi has been extended to handle reception of L-SIG and reception of non-legacy header differently.</li>
  <li>LTE/EPC model has been enhanced to allow the simulation user to test more realistic topologies related to the core network:</li>
    <ul>
      <li>SGW, PGW and MME are full nodes.</li>
      <li>There are P2P links between core network nodes.</li>
      <li>New S5 interface between SGW and PGW nodes based on GTPv2-C protocol.</li>
      <li>Allow simulations with multiple SGWs and PGWs.</li>
    </ul>
  </li>
  <li>LTE eNB RRC is extended to support:</li>
    <ul>
      <li>S1 signalling with the core network is initiated after the RRC connection establishment procedure is finished.</li>
      <li>New ATTACH_REQUEST state to wait for finalization of the S1 signalling with the core network.</li>
      <li>New InitialContextSetupRequest primitive of the S1 SAP that is received by the eNB RRC when the S1 signalling from the core network is finished.</li>
    </ul>
  </li>
  <li> A new buffer has been introduced in the LteEnbRrc class. This buffer will be used by a target eNB during handover to buffer the packets comming from a source eNB on X2 inteface. The target eNB will buffer this data until it receives RRC Connection Reconfiguration Complete from a UE.
  </li>
  <li> The default qdisc installed on single-queue devices (such as PointToPoint, Csma and Simple) is now <b>FqCoDel</b> (instead of PfifoFast). On multi-queue devices (such as Wifi), the default root qdisc is now <b>Mq</b> with as many FqCoDel child qdiscs as the number of device queues. The new defaults are motivated by the willingness to align with the behavior of major Linux distributions and by the need to preserve the effectiveness of Wifi EDCA Functions in differentiating Access Categories (see issue #35).</li>
  <li>LTE RLC TM mode does not report anymore the layer-to-layer delay, as it misses (by standard) an header to which attach the timestamp tag. Users can switch to the PDCP layer delay measurements, which must be the same.</li>
  <li> Token Bank Fair Queue Scheduler (ns3::FdTbfqFfMacScheduler) will not anymore schedule a UE, which does not have any RBG left after removng the RBG from its allocation map if the computed TB size is greater than the "budget" computed in the scheduler.
  </li>
  <li> LTE module now supports the <b>Radio Link Failure (RLF)</b> functionality. This implementation introduced following key behavioral changes:
    <ul>
      <li> The UE RRC state will not remain in "CONNECTED_NORMALLY" state if the DL control channel SINR is below a set threshold.</li>
      <li> The LTE RRC protocol APIs of UE i.e., LteUeRrcProtocolIdeal, LteUeRrcProtocolReal have been extended to send an ideal (i.e., using SAPs instead to transmitting over the air) UE context remove request to the eNB. Similarly, the eNB RRC protocol APIs, i.e, LteEnbRrcProtocolIdeal and LteEnbRrcProtocolReal have been extended to receive this ideal UE context remove request.</li>
      <li> The UE will not synchronize to a cell whose RSRP is less than -140 dBm.</li>
      <li> The non-contention based preambles during a handover are re-assigning to an UE only if it has not been assign to another UE (An UE can be using the preamble even after the expiryTime duration).</li>
      <li> The RachConfigCommon structure in LteRrcSap API has been extended to include "TxFailParam". This new field would enable an eNB to indicate how many times T300 timer can expire at the UE. Upon reaching this count, the UE aborts the connection establishment, and performs the cell selection again. See TS 36.331 5.3.3.6. </li>
      <li> The timer T300 in LteUeRrc class is now bounded by the standard min and max values defined in 3GPP TS 36.331.</li>
    </ul>
  </li>
</ul>

<hr>
<h1>Changes from ns-3.28 to ns-3.29</h1>
<h2>New API:</h2>
<ul>
  <li> CommandLine can now handle non-option (positional) arguments. </li>
  <li> Added CommandLine::Parse (const std::vector<std::string>> args) </li>
  <li> NS_LOG_FUNCTION can now log the contents of vectors </li>
  <li> A new position allocator has been added to the buildings module, allowing
nodes to be placed outside of buildings defined in the scenario.</li>
  <li> The Hash() method has been added to the QueueDiscItem class to compute the
    hash of various fields of the packet header (depending on the packet type).</li>
  <li> Added a priority queue disc (PrioQueueDisc).</li>
  <li> Added 3GPP HTTP model
  <li> Added TCP PRR as recovery algorithm
  <li> Added a new trace source in StaWifiMac for tracing beacon arrivals</li>
  <li> Added a new helper method to ApplicationContainer to start applications with some jitter around the start time</li>
  <li> (network) Add a method to check whether a node with a given ID is within a NodeContainer.</li>

</ul>
<h2>Changes to existing API:</h2>
<ul>
  <li>TrafficControlHelper::Install now only includes root queue discs in the returned
    QueueDiscContainer.</li>
  <li>Recovery algorithms are now in a different class, instead of being tied to TcpSocketBase.
    Take a look to TcpRecoveryOps for more information.</li>
  <li>The Mode, MaxPackets and MaxBytes attributes of the Queue class, that had been deprecated in favor of the MaxSize attribute in ns-3.28, have now been removed and cannot be used anymore. Likewise, the methods to get/set the old attributes have been removed as well.  Commands such as:
<pre>
  Config::SetDefault ("ns3::QueueBase::MaxPackets", UintegerValue (4));
</pre>
should now be written as:
<pre>
  Config::SetDefault ("ns3::QueueBase::MaxSize", QueueSizeValue (QueueSize (QueueSizeUnit::PACKETS, 4)));
</pre>
or with a string value with 'b' (bytes) or 'p' (packets) suffix, such as:
<pre>
  Config::SetDefault ("ns3::QueueBase::MaxSize", StringValue ("4p"));
</pre>
  </li>
  <li>The Limit attribute of the PfifoFastQueueDisc class, that had been deprecated in favor of the MaxSize attribute in ns-3.28, has now been removed and cannot be used anymore. Likewise, the methods to get/set the old Limit attribute have been removed as well. The GetMaxSize/SetMaxSize methods of the base QueueDisc class must be used instead.</li>
  <li>The Mode, MaxPackets and MaxBytes attributes of the CoDelQueueDisc class, that had been deprecated in favor of the MaxSize attribute in ns-3.28, have now been removed and cannot be used anymore. Likewise, the methods to get/set the old attributes have been removed as well. The GetMaxSize/SetMaxSize methods of the base QueueDisc class must be used instead.</li>
  <li>The PacketLimit attribute of the FqCoDelQueueDisc class, that had been deprecated in favor of the MaxSize attribute in ns-3.28, has now been removed and cannot be used anymore. Likewise, the methods to get/set the old PacketLimit attribute have been removed as well. The GetMaxSize/SetMaxSize methods of the base QueueDisc class must be used instead.</li>
  <li>The Mode and QueueLimit attributes of the PieQueueDisc class, that had been deprecated in favor of the MaxSize attribute in ns-3.28, have now been removed and cannot be used anymore. Likewise, the methods to get/set the old attributes have been removed as well. The GetMaxSize/SetMaxSize methods of the base QueueDisc class must be used instead.</li>
  <li>The Mode and QueueLimit attributes of the RedQueueDisc class, that had been deprecated in favor of the MaxSize attribute in ns-3.28, have now been removed and cannot be used anymore. Likewise, the methods to get/set the old attributes have been removed as well. The GetMaxSize/SetMaxSize methods of the base QueueDisc class must be used instead.</li>
  <li> Several traffic generating applications have additional trace sources that export not only the transmitted or received packet but also the source and destination addresses.</li>
  <li>The returned type of <b>GetNDevices</b> methods in <b>Channel</b> and subclasses derived from it were changed from uint32_t to std::size_t. Likewise, the input parameter type of <b>GetDevice</b> in <b>Channel</b> and its subclasses were changed from uint32_t to std::size_t.</li>
  <li>Wifi classes <b>DcfManager</b>, <b>DcaTxop</b> and <b>EdcaTxopN</b> were renamed to <b>ChannelAccessManager</b>, <b>Txop</b> and <b>QosTxop</b>, respectively.</li>
  <li>QueueDisc::DequeuePeeked has been merged into QueueDisc::Dequeue and hence no longer exists.</li>
  <li>The QueueDisc base class now provides a default implementation of the DoPeek private method
  based on the QueueDisc::PeekDequeue method, which is now no longer available.</li>
  <li>The QueueDisc::SojournTime trace source is changed from a TracedValue to a TracedCallback; callbacks that hook this trace must provide one ns3::Time argument, not two.</li>
  <li>To avoid the code duplication in SingleModelSpectrumChannel and MultiModelSpectrumChannel classes, the attributes MaxLossDb and PropagationLossModel, and the traces PathLoss and TxSigParams are moved to the base class SpectrumChannel. Similarly, the functions AddPropagationLossModel, AddSpectrumPropagationLossModel, SetPropagationDelayModel and GetSpectrumPropagationLossModel are now defined in SpectrumChannel class. Moreover, the TracedCallback signature of LossTracedCallback has been updated from :
  <pre>
   typedef void (* LossTracedCallback) (Ptr&#60;SpectrumPhy&#62 txPhy, Ptr&#60;SpectrumPhy&#62 rxPhy, double lossDb);
  </pre>
   To :
  <pre>
   typedef void (* LossTracedCallback) (Ptr&#60;const SpectrumPhy&#62 txPhy, Ptr&#60;const SpectrumPhy&#62 rxPhy, double lossDb);
  </pre></li>
  <li>For the sake of LTE module API consistency the IPV6 related functions AssignUeIpv6Address and GetUeDefaultGatewayAddress6 are now declared in EpcHelper base class. Thus, these functions are now declared as virtual in the child classes, i.e., EmuEpcHelper and PointToPointEpcHelper.</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li>Waf upgraded from 1.8.19 to 2.0.9, and ns-3 build scripts aligned to the new API.</li>
  <li>The '--no32bit-scan' argument is removed from Waf apiscan; generation of ILP32 bindings is now automated from the LP64 bindings.</li>
  <li> When using on newer compilers, new warnings may trigger build failures.
The --disable-werror flag can be passed to Waf at configuration time to turn
off the Werror behavior.</li>
  <li> GTK+3 libraries (including PyGObject, GooCanvas2) are needed for the Pyviz visualizer, replacing GTK+2 libraries.</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
  <li>FqCoDelQueueDisc now computes the hash of the packet's 5-tuple to determine
    the flow the packet belongs to, unless a packet filter has been configured.
    The previous behavior is simply obtained by not configuring any packet filter.
    Consequently, the FqCoDelIpv{4,6}PacketFilter classes have been removed.</li>
  <li> ARP packets now pass through the traffic control layer, as in Linux. </li>
  <li> The maximum size UDP packet of the UdpClient application is no longer limited to 1500 bytes.</li>
  <li> The default values of the <b>MaxSlrc</b> and <b>FragmentationThreshold</b> attributes in WifiRemoteStationManager were changed from 7 to 4 and from 2346 to 65535, respectively.
</ul>

<hr>
<h1>Changes from ns-3.27 to ns-3.28</h1>
<h2>New API:</h2>
<ul>
  <li> When deserializing Packet contents, <b>Header::Deserialize (Buffer::Iterator start)</b> and <b>Trailer::Deserialize (Buffer::Iterator start)</b> can not successfully deserialize variable-length headers and trailers.  New variants of these methods that also include an 'end' parameter are now provided.</li>
  <li> Ipv[4,6]AddressGenerator can now check if an address is allocated (<b>Ipv[4,6]AddressGenerator::IsAddressAllocated</b>) or a network has some allocated address (<b>Ipv[4,6]AddressGenerator::IsNetworkAllocated</b>).</li>
  <li> LTE UEs can now use IPv6 to send and receive traffic.</li>
  <li> UAN module now supports an IP stack.</li>
  <li> Class <b>TcpSocketBase</b> trace source <i>CongestionWindowInflated</i> shows the values with the in-recovery inflation and the post-recovery deflation.
  <li> Added a FIFO queue disc (FifoQueueDisc) and the Token Bucket Filter (TbfQueueDisc).</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
  <li> Class <b>LrWpanMac</b> now supports extended addressing mode. Both <b>McpsDataRequest</b> and <b>PdDataIndication</b> methods will now use extended addressing if <b>McpsDataRequestParams::m_srcAddrMode</b> or <b>McpsDataRequestParams::m_dstAddrMode</b> are set to <b>EXT_ADDR</b>.</li>
  <li> Class <b>LteUeNetDevice</b> MAC address is now a 64-bit address and can be set during construction.</li>
  <li> Class <b>TcpSocketBase</b> trace source <i>CongestionWindow</i> shows the values without the in-recovery inflation and the post-recovery deflation; the old behavior has been moved to the new trace source <i>CongestionWindowInflated</i>.
  <li>The Mode, MaxPackets and MaxBytes attributes of the Queue class have been deprecated in favor of the MaxSize attribute. Old attributes can still be used, but using them will be no longer possible in one of the next releases. The methods to get/set the old attributes will be removed as well.</li>
  <li>The attributes of the QueueDisc subclasses that separately determine the mode and the limit of the QueueDisc have been deprecated in favor of the single MaxSize attribute.</li>
  <li>The GetQueueSize method of some QueueDisc subclasses (e.g., RED) has been removed and replaced by the GetCurrentSize method of the QueueDisc base class.</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li> The C++ standard used during compilation (default std=c++11) can be now be changed via the CXXFLAGS variable.</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
  <li>All Wi-Fi management frames are now transmitted using the lowest basic rate.</li>
  <li>The Wi-Fi spectrum model now takes into account adjacent channels through OFDM transmit spectrum masks.</li>
  <li> The CsmaNetDevice::PhyTxBeginTrace will trace all attempts to transmit, even those that result in drops. Previously, eventual channel drops were excluded from this trace.</l>
  <li>The TCP congestion window trace now does not report on window inflation during fast recovery phase because it is no longer internally maintained as an inflated value (a separate trace called CongestionWindowInflated can be used to recover the old trace behavior).</li>
</ul>

<hr>
<h1>Changes from ns-3.26 to ns-3.27</h1>
<h2>New API:</h2>
<ul>
<li>Added <code>Vector{2,3}D.GetLength ()</code>.</li>
<li>Overloaded <code>operator+</code> and <code>operator-</code> for <code>Vector{2,3}D</code>.</li>
<li>Added iterator version of WifiHelper::Install() to install Wi-Fi devices on range of nodes.</li>
<li>Added a new attribute in TcpSocketBase to track the advertised window.</li>
<li>Included the model of <b>TCP Ledbat</b>.</li>
<li>Included the TCP SACK-based loss recovery algorithm outlined in RFC 6675.</li>
<li>Added <b>TCP SACK</b> and the <b>SACK emulation</b>. Added an Attribute to TcpSocketBase class,
    called "Sack", to enable or disable the SACK option usage.</li>
<li>In 'src/wifi', several changes were made to enable partial <b>802.11ax</b> High Efficiency (HE) support:
    <ul>
      <li>A new standard value has been added that enables the new 11ax data rates.</li>
      <li>A new 11ax preamble has been added.</li>
      <li>A new attribute was added to configure the guard interval duration for High Efficiency (HE) PHY entities. This attribute can be set using the YansWifiPhyHelper.</li>
      <li>A new information element has been added:  HeCapabilities. This information element is added to the MAC frame header if the node is a HE node. This HeCapabilites information element is used to advertise the HE capabilities of the node to other nodes in the network.</li>
    </ul>
</li>
<li> A new class were added for the RRPAA WiFi rate control mechanism.</li>
<li>Included carrier aggregation feature in LTE module</li>
    <ul>
      <li>LTE model is extended to support carrier aggregation feature according to 3GPP Release 10, for up to 5 component 
      carriers. </li>
      <li>InstallSingleEnbDevice and InstalSingeUeDevice functions of LteHelper are now constructing LteEnbDevice and LteUeDevice 
      according to CA architecture. Each device, UE and eNodeB contains an instance of component carrier manager, and may 
      have several component carrier instances.</li>
      <li>SAP interfaces are extended to include CA message exchange functionality.</li>
      <li>RRC connection procedure is extended to allow RRC connection reconfiguration for the configuration of the secondary carriers.</li>
      <li>RRC measurement reporting is extended to allow measurement reporting from the secondary carriers.</li>
      <li>LTE traces are extended to include component carrier id.</li>
    </ul>
</li>
<li>Function <b>PrintRoutingTable</b> has been extended to add an optional Time::Units
    parameter to specify the time units used on the report.  The new parameter is
    optional and if not specified defaults to the previous behavior (Time::S).
</li>
<li><b>TxopTrace</b>: new trace source exported by EdcaTxopN.</li>
<li>A <b>GetDscpCounts</b> method is added to <b>Ipv4FlowClassifier</b> and <b>Ipv6FlowClassifier</b>
    which returns a vector of pairs (dscp,count), each of which indicates how many packets with the
    associated dscp value have been classified for a given flow.
</li>
<li>MqQueueDisc, a multi-queue aware queue disc modelled after the mq qdisc in Linux, has been introduced.
</li>
<li>Two new methods, <b>QueueDisc::DropBeforeEnqueue()</b> and <b>QueueDisc::DropAfterDequeue()</b> have
    been introduced to replace <b>QueueDisc::Drop()</b>. These new methods require the caller to specify the
    reason why a packet was dropped. Correspondingly, two new trace sources ("DropBeforeEnqueue" and
    "DropAfterDequeue") have been added to the QueueDisc class, providing both the items that were dropped
    and the reason why they were dropped. 
</li>
<li>Added <b>QueueDisc::GetStats()</b> which returns detailed statistics about the operations of
    a queue disc. Statistics can be accessed through the member variables of the returned object and
    by calling the <b>GetNDroppedPackets()</b>, <b>GetNDroppedBytes()</b>, <b>GetNMarkedPackets()</b> and <b>GetNMarkedBytes()</b> methods on the returned object. Such methods return the number of packets/bytes
    dropped/marked for the specified reason (passed as argument). Consequently:
    <ul>
      <li>A number of methods of the QueueDisc class have been removed: <b>GetTotalReceivedPackets()</b>,
      <b>GetTotalReceivedBytes()</b>, <b>GetTotalDroppedPackets()</b>, <b>GetTotalDroppedBytes()</b>,
      <b>GetTotalRequeuedPackets()</b>, <b>GetTotalRequeuedBytes()</b>.</li>
      <li>The <b>Stats</b> struct and the <b>GetStats()</b> method of <b>RedQueueDisc</b> and <b>PieQueueDisc</b> have been removed and replaced by those of the QueueDisc base class.</li>
      <li>The <b>GetDropOverLimit</b> and <b>GetDropCount</b> methods of <b>CoDelQueueDisc</b> have been removed.
      The values they returned can be obtained by calling, respectively,
      GetStats ().GetNDroppedPackets (CoDelQueueDisc::OVERLIMIT_DROP) and
      GetStats ().GetNDroppedPackets (CoDelQueueDisc::TARGET_EXCEEDED_DROP). The "DropCount" trace of
      <b>CoDelQueueDisc</b> has been removed as well. Packets dropped because the target is exceeded can
      be obtained through the new "DropAfterDequeue" trace of the QueueDisc class.</li>
    </ul>
</li>
<li> The new <b>QueueDisc::Mark()</b> method has been introduced to allow subclasses to request to mark a packet.
     The  caller must specify the reason why the packet must be marked. Correspondingly, a new trace source ("Mark")
     has been added to the QueueDisc class, providing both the items that were marked and the reason why they
     were marked.
</li>
<li>A new trace source, <b>SojournTime</b>, is exported by the QueueDisc base class to provide the
    sojourn time of every packet dequeued from a queue disc. This has been made possible by adding a
    timestamp to QueueDiscItem objects, which can be set/get through the new <b>GetTimeStamp()</b> and
    <b>SetTimeStamp()</b> methods of the QueueDiscItem class. The <b>CoDel</b> queue disc now makes use of such feature of the base class, hence its Sojourn trace source and the CoDelTimestampTag class
    have been removed.
</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li><b>ParetoRandomVariable</b> "Mean" attribute has been deprecated, 
    the "Scale" Attribute have to be used instead.
    Changing the Mean attribute has no more an effect on the distribution.
    See the documentation for the relationship between Mean, Scale and Shape. 
</li>
<li>The default logging timestamp precision has been changed from 6 digits
    to 9 digits, with a fixed format to ensure that 9 digits to the right of
    the decimal point are always printed.  Previously, default C++ iostream
    precision and formatting was used.
</li>
<li>Abstract base class <b>WifiChannel</b> has been removed. As a result, a Channel type instead of a WifiChannel type
is now exported by WifiNetDevice.</li>
<li> The <b>GetPacketSize</b> method of <b>QueueItem</b> has been renamed <b>GetSize</b>
</li>
<li> The <b>DequeueAll</b> method of <b>Queue</b> has been renamed <b>Flush</b>
</li>
<li>The attributes <b>WifiPhy::TxAntennas</b> and <b>WifiPhy::RxAntennas</b>,
    and the related accessor methods, were replaced by <b>WifiPhy::MaxSupportedTxSpatialStreams</b>
    and <b>WifiPhy::MaxSupportedRxSpatialStreams</b>. A new attribute <b>WifiPhy::Antennas</b>
    was added to allow users to define the number of physical antennas on the device.
</li>
<li>Sockets do not receive anymore broadcast packets, unless they are bound to an "Any" address (0.0.0.0)
    or to a subnet-directed broadcast packet (e.g., x.y.z.0 for a /24 noterok).
    As in Linux, the following rules are now enforced:
    <ul>
    <li> A socket bound to 0.0.0.0 will receive everything.</li>
    <li> A socket bound to x.y.z.0/24 will receive subnet-directed broadcast (x.y.z.255) and unicast packets.</li>
    <li> A socket bound to x.y.z.w will only receive unicast packets.</li>
    </ul> 
    <b>Previously, a socket bound to an unicast address received also subnet-directed broadcast packets. 
    This is not anymore possible</b>.
</li>
<li>You can now Bind as many socket as you want to an address/port, provided that they are bound to different NetDevices.
    Moreover, BindToNetDevice does not anymore call Bind. In other terms, Bind and BindToNetDevice can be called
    in any order.
    However, it is suggested to use BindToNetDevice <i>before</i> Bind in order to avoid conflicts.
</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
<li> The API scanning process for Python bindings now relies on CastXML, and only 64-bit scans are presently supported (Linux 64-bit systems).  Generation of 32-bit scans is documented in the Python chapter of the ns-3 manual.
</li>
<li> Modules can now be located in the 'contrib/' directory in addition to 'src/'
</li>
<li> Behavior for running Python programs was aligned with that of C++ programs; the list of modules built is no longer printed out.
</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li><b>MultiModelSpectrumChannel</b> does not call StartRx for receivers that
    operate on subbands orthogonal to transmitter subbands. Models that depend
    on receiving signals with zero power spectral density from orthogonal bands
    may change their behavior.
    See <a href=https://www.nsnam.org/bugzilla/show_bug.cgi?id=2467>bug 2467</a>
    for discussion.
</li>
<li><b>Packet Tag objects</b> are no longer constrained to fit within 21 
    bytes; a maximum size is no longer enforced.
</li>
  <li> The default value of the <b>TxGain</b> and <b>RxGain</b> attributes in WifiPhy was changed from 1 dB to 0 dB.
  </li>
  <li> The reported SNR by WifiPhy::MonitorSnifferRx did not include the RxNoiseFigure, but now does; see <a href=https://www.nsnam.org/bugzilla/show_bug.cgi?id=2783>bug 2783</a> for discussion.
  </li>
<li><b>Queue</b> has been redesigned as a template class object, where the type parameter
    specifies the type of items to be stored in the queue. As a consequence:
    <ul>
      <li>Being a subclass of Queue, <b>DropTailQueue</b> is a template class as well.
      <li>Network devices such as SimpleNetDevice, PointToPointNetDevice and CsmaNetDevice
      use a queue of type Queue&lt;Packet&gt; to store the packets to transmit. The SetQueue
      method of their helpers, however, can still be invoked as, e.g.,
      SetQueue ("ns3::DropTailQueue") instead of, e.g., SetQueue
      ("ns3::DropTailQueue&lt;Packet&gt;").</li>
      <li>The attributes <b>Mode</b>, <b>MaxPackets</b> and <b>MaxBytes</b> are now
      defined by the QueueBase class (which Queue is derived from).</li>
    </ul>
</li>
<li>Queue discs that can operate both in packet mode and byte mode (Red, CoDel, Pie) define their own
    enum QueueDiscMode instead of using QueueBase::QueueMode.
</li>
<li>The CoDel, PIE and RED queue discs require that the size of the internal queue is the same as
    the queue disc limit (previously, it was allowed to be greater than or equal).
</li>
  <li> The default value of the <b>EnableBeaconJitter</b> attribute in ApWifiMac was changed from false to true.
  </li>
  <li> The NormalClose() callback of a TcpSocket object used to fire upon leaving TIME_WAIT state (2*MSL after FINs have been exchanged).  It now fires upon entering TIME_WAIT state.  Timing of the callback for the other path to state CLOSED (through LAST_ACK) has not been changed.
  </li>
</ul>

<hr>
<h1>Changes from ns-3.25 to ns-3.26</h1>
<h2>New API:</h2>
<ul>
<li>A <b>SocketPriorityTag</b> is introduced to carry the packet priority. Such a tag
    is added to packets by sockets that support this mechanism (UdpSocketImpl,
    TcpSocketBase and PacketSocket). The base class Socket has a new SetPriority
    method to set the socket priority. When the IPv4 protocol is used, the
    priority is set based on the ToS. See the Socket options section of the
    Network model for more information.
</li>
<li>A <b>WifiNetDevice::SelectQueue</b> method has been added to determine the user
    priority of an MSDU. This method is called by the traffic control layer before
    enqueuing a packet in the queue disc, if a queue disc is installed on
    the outgoing device, or passing a packet to the device, otherwise. The
    user priority is set to the three most significant bits of the DS field
    (TOS field in case of IPv4 and Traffic Class field in case of IPv6). The
    packet priority carried by the SocketPriorityTag is set to the user priority.
</li>
<li>The <b>PfifoFastQueueDisc</b> classifies packets into bands based on their priority.
    See the pfifo_fast queue disc section of the Traffic Control Layer model
    for more information.
</li>
<li>A new class <b>SpectrumWifiPhy</b> has been introduced that makes use of the 
    Spectrum module.  Its functionality and API is currently very similar to that 
    of the YansWifiPhy, especially because it reuses the same InterferenceHelper 
    and ErrorModel classes (for this release).  Some example programs in the 
    'examples/wireless/' directory, such as 'wifi-spectrum-per-example.cc', 
    illustrate how the SpectrumWifiPhy class can be substituted for the default 
    YansWifiPhy PHY model.
</li>
<li>We have added support for generating traces for the
    <a href="https://wilseypa.github.io/desMetrics">DES Metrics</a> project.
    These can be enabled by adding <tt>--enable-des-metrics</tt> at configuration;
    you must also use <tt>CommandLine</tt> in your script.  See the API docs
    for class <b>DesMetrics</b> for more details.
</li>
<li> The traffic control module now includes the <b>FQ-CoDel</b> and <b>PIE</b> queue disc 
    models, and behavior corresponding to Linux <b>Byte Queue Limits (BQL)</b>.
</li>
<li> Several new TCP congestion control variants were introduced, including
    <b>TCP Vegas, Scalable, Veno, Illinois, Bic, YeAH, and H-TCP</b> 
    congestion control algorithms.
</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
<li><b>SocketAddressTag</b> was a long-standing approach to approximate the POSIX
    socket recvfrom behavior (i.e., to know the source address of a packet) 
    without actually calling RecvFrom.  Experience with this revealed that
    this option was difficult to use with tunnels (the new tag has to 
    replace the old one).  Moreover, there is no real need 
    to create a new API when there is a an existing one (i.e., RecvFrom).
    As a consequence, SocketAddressTag has been completely removed from ns-3.
    Users can use RecvFrom (for UDP), GetPeerName (for TCP), or similar. 
</li>
<li><b>InetSockAddress</b> can now store a ToS value, which can be set through its
    SetTos method. The Bind and Connect methods of UDP (UdpSocketImpl) and
    TCP (TcpSocketBase) sockets set the socket ToS value to the value provided
    through the address input parameter (of type InetSockAddress). See the
    Socket options section of the Network model for more information.
</li>
<li>The <b>QosTag</b> is removed as it has been superseded by the SocketPriorityTag.</li>
<li>The <b>Ipv4L3Protocol::DefaultTos</b> attribute is removed.</li>
<li>The attributes <b>YansWifiPhy::Frequency, YansWifiPhy::ChannelNumber, and 
    YansWifiPhy::ChannelWidth</b>, and the related accessor methods, were moved to 
    base class WifiPhy.  YansWifiPhy::GetChannelFrequencyMhz() was deleted.  
    A new method WifiPhy::DefineChannelNumber () was added to allow users to 
    define relationships between channel number, standard, frequency, and channel width.
</li>
<li>The class <b>WifiSpectrumValueHelper</b> has been refactored; previously it 
    was an abstract base class supporting the WifiSpectrumValue5MhzFactory spectrum 
    model.  It now contains various static member methods supporting the creation 
    of power spectral densities with the granularity of a Wi-Fi OFDM subcarrier 
    bandwidth.  The class <b>WifiSpectrumValue5MhzFactory</b> and its API remain but 
    it is not subclassed.
 </li>
<li>A new Wifi method <b>InterferenceHelper::AddForeignSignal</b> has been introduced to 
    support use of the SpectrumWifiPhy (so that non-Wi-Fi signals may be handled 
    as noise power).
</li>
<li>A new Wifi attribute <b>Dcf::TxopLimit</b> has been introduced to add support for 802.11e TXOP.
</li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li> A new waf build option, <tt>--check-config</tt>, was added to allow users to print the current configuration summary, as appears at the end of ./waf configure.  See bug 2459 for discussion.</li>
  <li> The <tt>configure</tt> summary is now sorted, to make it easier to check the status of optional features.</li>
</ul>
<h2>Changed behavior:</h2>
This section is for behavioral changes to the models that were not due to a bug fix.
<ul>
  <li>The relationship between Wi-Fi channel number, frequency, channel width, 
      and Wi-Fi standard has been revised (see bug 2412).  Previously, ChannelNumber 
      and Frequency were attributes of class YansWifiPhy, and the frequency was 
      defined as the start of the band.  Now, Frequency has been redefined to be 
      the center frequency of the channel, and the underlying device relies on 
      the pair of frequency and channel width to control behavior; the channel 
      number and Wi-Fi standard are used as attributes to configure frequency 
      and channel width.  The wifi module documentation discusses this change 
      and the new behavior.
  </li>
  <li>AODV now honors the TTL in RREQ/RREP and it uses a method 
      compliant with <a href="http://www.ietf.org/rfc/rfc3561.txt">RFC 3561</a>.      The node search radius is increased progressively. This could increase 
      slightly the node search time, but it also decreases the network 
      congestion.
  </li>
</ul>

<hr>
<h1>Changes from ns-3.24 to ns-3.25</h1>
<h2>New API:</h2>
<ul>
  <li> In 'src/internet/test', a new environment is created to test TCP properties.</li>
  <li> The 'src/traffic-control' module has been added, with new API for adding and configuring queue discs and packet filters.</li>
  <li> Related to traffic control, a new interface has been added to the
NetDevice to provide a queue interface to access device queue state and
register callbacks used for flow control.</li>
  <li> In 'src/wifi', a new rate control (MinstrelHT) has been added for
802.11n/ac modes.</li>
  <li> In 'src/wifi', a new helper (WifiMacHelper) is added and is a merged helper from all previously existing MAC helpers (NqosWifiMacHelper, QosWifiMacHelper, HtWifiMacHelper and VhtWifiMacHelper).</li>
  <li> It is now possible to use RIPv2 in IPv4 network simulations.</li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
  <li>TCP-related changes:
    <ul>
      <li>Classes TcpRfc793, TcpTahoe, and TcpReno were removed.</li>
      <li>The 'TcpNewReno' log component was effectively replaced by 'TcpCongestionOps'
      <li>TCP Hybla and HighSpeed have been added.</li>
      <li>Added the concept of Congestion State Machine inside TcpSocketBase.</li>
      <li>Merged Fast Recovery and Fast Retransmit inside TcpSocketBase.</li>
      <li>Some member variables have been moved from TcpSocketBase inside TcpSocketState. Attributes are not touched.</li>
      <li>Congestion control split from TcpSocketBase as subclass of TcpCongestionOps.</li>
      <li>Added Rx and Tx callbacks on TcpSocketBase.</li>
      <li>Added BytesInFlight trace source on TcpSocketBase. The trace is updated when the implementation requests the value.</li>
      <li>Added attributes about the number of connection and data retransmission attempts.</li>
    </ul>
  </li>
  <li> ns-3 is now capable of serializing SLL (a.k.a. cooked) headers.
       This is used in DCE to allow the generation of pcap directly readable by wireshark.
  </li>
  <li> In the WifiHelper class in the wifi module, Default has been declared deprecated. This is now immediately handled by the constructor of the class.</li>
  <li> The API for configuring 802.11n/ac aggregation has been modified to be more user friendly. As any MAC layer attributes, aggregation parameters can now also be configured through WifiMacHelper::SetType. </li>
  <li> The class Queue and subclasses derived from it have been changed in two ways:
  <ul>
    <li>Queues no longer enqueue simple Packets but instead enqueue QueueItem objects, which include Packet but possibly other information such as headers.</li>
    <li>The attributes governing the mode of operation (packets or bytes) and the maximum size have been moved to base class Queue.</li>
  </ul>
  </li>
  <li> Users of advanced queues (RED, CoDel) who have been using them directly in the NetDevice will need to adjust to the following changes:
    <ul>
      <li> RED and CoDel are no longer specializations of the Queue class, but are now specializations of the new QueueDisc class. This means that RED and CoDel can now be installed in the context of the new Traffic Control layer instead of as queues in (some) NetDevices. The reason for such a change is to make the ns-3 stack much more similar to that of real operating systems (Linux has been taken as a reference).  Queuing disciplines such as RED and CoDel can now be tested with all the NetDevices, including WifiNetDevices. </li>
      <li> NetDevices still use queues to buffer packets. The only subclass of Queue currently available for this purpose is DropTailQueue. If one wants to approximate the old behavior, one needs to set the DropTailQueue MaxPackets attribute to very low values, e.g., 1.</li>
      <li> The Traffic Control layer features a mechanism by which packets dropped by the NetDevice are requeued in the queue disc (more precisely: if NetDevice::Send returns false, the packet is requeued), so that they are retransmitted later. This means that the MAC drop traces may include packets that have not been actually lost, because they have been dropped by the device, requeued by the traffic control layer and successfully retransmitted. To get the correct number of packets that have been actually lost, one has to subtract the number of packets requeued from the number of packets dropped as reported by the MAC drop trace. </li>
    </ul>
  </li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li> Waf was upgraded to 1.8.19</li>
  <li> A new waf build option, --check-profile, was added to allow users to check the currently active build profile.  It is discussed in bug 2202 in the tracker.</li>
</ul>
<h2>Changed behavior:</h2>
This section is for behavioral changes to the models that were not due to a bug fix.
<ul>
  <li>TCP behavioral changes:
    <ul>
      <li>TCP closes connection after a number of failed segment retries,
        rather than trying indefinitely. The maximum number of retries, for both SYN
        attempts and data attempts, is controlled by attributes.</li>
      <li>Congestion algorithms not compliant with Fast Retransmit
        and Fast Recovery (TCP 793, Reno, Tahoe) have been removed.</li>
    </ul>
  </li>
  <li> 802.11n/ac MPDU aggregation is now enabled by default for both AC_BE and AC_VI.</li>
  <li> The introduction of the traffic control layer leads to some additional buffering by default in the stack; when a device queue fills up, additional packets become enqueued at the traffic control layer.</li>
</ul>

<hr>
<h1>Changes from ns-3.23 to ns-3.24</h1>
<h2>New API:</h2>
<ul>
  <li>In 'src/wifi', several changes were made to enable partial 802.11ac support:
    <ul>
      <li>A new helper (VhtWifiMacHelper) was added to set up a Very high throughput (VHT) MAC entity.</li>
      <li>A new standard value has been added that enables the new 11ac data rates.</li>
      <li>A new 11ac preamble has been added.</li>
      <li>A new information element has been added:  VhtCapabilities. This information element is added to the MAC frame header if the node is a VHT node. This VhtCapabilites information element is used to advertise the VHT capabilities of the node to other nodes in the network.</li>
    </ul>
  </li>
  <li>The ArpCache API was extended to allow the manual removal of ArpCache entries and the addition of permanent (static) entries for IPv4.
  </li>
  <li> The SimpleChannel in the 'network' module now allows per-NetDevice blacklists, in order to do hidden terminal testcases.
  </li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
  <li> The signatures on several TcpHeader methods were changed to take const arguments.</li>
  <li> class TcpL4Protocol replaces Send() methods with SendPacket(), and adds new methods to AddSocket() and RemoveSocket() from a node.  Also, a new PacketReceived() method was introduced to get the TCP header of an incoming packet and check its checksum.</li>
  <li> The CongestionWindow and SlowStartThreshold trace sources have been moved from the TCP subclasses such as NewReno, Reno, Tahoe, and Westwood to the TcpSocketBase class.</li>
  <li> The WifiMode object has been refactored:
    <ul>
      <li>11n data rates are now renamed according to their MCS value. E.g. OfdmRate65MbpsBW20MHz has been renamed into HtMcs7. 11ac data rates have been defined according to this new renaming.</li>
      <li>HtWifiMacHelper and VhtWifiMacHelper provide a helper to convert a MCS value into a data rate value.</li>
      <li>The channel width is no longer tied to the wifimode. It is now included in the TXVECTOR.</li>
      <li>The physical bitrate is no longer tied to the wifimode. It is computed based on the selected wifimode and on the TXVECTOR parameters (channel width, guard interval and number of spatial streams).</li>
    </ul>
  </li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li> Waf was upgraded to 1.8.12</li>
  <li> Waf scripts and test.py test runner program were made compatible with Python 3</li>
</ul>
<h2>Changed behavior:</h2>
This section is for behavioral changes to the models that were not due to a bug fix.
<ul>
</ul>

<hr>
<h1>Changes from ns-3.22 to ns-3.23</h1>
<h2>New API:</h2>
<ul>
  <li> The mobility module includes a GeographicPositions class used to
convert geographic to cartesian coordinates, and to generate randomly
distributed geographic coordinates.
  </li>
  <li>  The spectrum module includes new TvSpectrumTransmitter classes and helpers to create television transmitter(s) that transmit PSD spectrums customized by attributes such as modulation type, power, antenna type, channel frequency, etc.
  </li>
</ul>
<h2>Changes to existing API:</h2>
<ul>
  <li> In LteSpectrumPhy, LtePhyTxEndCallback and the corresponding methods have been removed, since they were unused.
  </li>
  <li> In the DataRate class in the network module, CalculateTxTime has been declared deprecated.  CalculateBytesTxTime and CalculateBitsTxTime are to be used instead.  The return value is a Time, instead of a double.
  </li>
  <li> In the Wi-Fi InterferenceHelper, the interference event now takes the WifiTxVector as an input parameter, instead of the WifiMode.  A similar change was made to the WifiPhy::RxOkCallback signature.
  </li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li> None </li>
</ul>
<h2>Changed behavior:</h2>
This section is for behavioral changes to the models that were not due to a bug fix.
<ul>
  <li> In Wi-Fi, HT stations (802.11n) now support two-level aggregation. The InterferenceHelper now distinguishes between the PLCP and regular payload reception, for higher fidelity modeling.  ACKs are now sent using legacy rates and preambles.  Access points now establish BSSBasicRateSet for control frame transmissions.  PLCP header and PLCP payload reception have been decoupled to improve PHY layer modeling accuracy.  RTS/CTS with A-MPDU is now fully supported.  
  </li>
  <li> The mesh module was made more compliant to the IEEE 802.11s-2012 standard and packet traces are now parseable by Wireshark.  
  </li>
</ul>

<hr>
<h1>Changes from ns-3.21 to ns-3.22</h1>
<h2>New API:</h2>
<ul>
  <li> New classes were added for the PARF and APARF WiFi power and rate control mechanisms. 
  </li>
  <li> Support for WiFi 802.11n MPDU aggregation has been added.
  </li>
  <li> Additional support for modeling of vehicular WiFi networks has been added, including the channel-access coordination feature of IEEE 1609.4.  In addition, a Basic Safety Message (BSM) packet generator and related statistics-gathering classes have been added to the wave module. 
  </li>
  <li> A complete LTE release bearer procedure is now implemented which can be invoked by calling the new helper method LteHelper::DeActivateDedicatedEpsBearer ().
  </li>
  <li> It is now possible to print the Neighbor Cache (ARP and NDISC) by using
       the RoutingProtocolHelper
  </li>
  <li> A TimeProbe class has been added to the data collection framework in 
       the stats module, enabling TracedValues emitting values of type 
       ns3::Time to be handled by the framework.
  </li>
  <li> A new attribute 'ClockGranularity' was added to the TcpSocketBase class,
to control modeling of RTO calculation.
  </li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
  <li> Several deprecated classes and class methods were removed, including EmuNetDevice, RandomVariable and derived classes, Packet::PeekData(), Ipv6AddressHelper::NewNetwork(Ipv6Address, Ipv6Prefix), Ipv6InterfaceContainer::SetRouter(), Ipv4Route::GetOutputTtl(), TestCase::AddTestCase(TestCase*), and TestCase::GetErrorStatus().
  </li>
  <li> Print methods involving routing tables and neighbor caches, in classes Ipv4RoutingHelper and Ipv6RoutingHelper, were converted to static methods.
  </li>  
  <li>PointerValue attribute types in class UanChannel (NoiseModel), UanPhyGen (PerModel and SinrModel), UanPhyDual (PerModelPhy1, PerModelPhy2, SinrModelPhy1, and SinrModelPhy2), and SimpleNetDevice (TxQueue), were changed from PointerValue type to StringValue type, making them configurable via the Config subsystem. 
  </li>
  <li> WifiPhy::CalculateTxDuration() and WifiPhy::GetPayloadDurationMicroSeconds () now take an additional frequency parameter.
  </li>
  <li> The attribute 'Recievers' in class YansWifiPhy was misspelled, so
       this has been corrected to 'Receivers'.
  </li>
  <li> We have now documented the callback function signatures
       for all TracedSources, using an extra (fourth) argument to
       TypeId::AddTraceSource to pass the fully-qualified name
       of the signature typedef.  To ensure that future TraceSources
       are similarly documented, the three argument version of 
       AddTraceSource has been deprecated.
  </li>	
  <li> The "MinRTO" attribute of the RttEstimator class was moved to the TcpSocketBase class.  The "Gain" attribute of the RttMeanDeviation class was replaced 
by new "Alpha" and "Beta" attributes.  
  </li>	
  <li> Attributes of the TcpTxBuffer and TcpRxBuffer class are now accessible through the TcpSocketBase class.
  </li>	
  <li> The LrWpanHelper class has a new constructor allowing users to configure a MultiModelSpectrumChannel as an option, and also provides Set/Get API to allow users to access the underlying channel object. 
  </li>
</ul>

<h2>Changes to build system:</h2>
<ul>
  <li> waf was upgraded to version 1.7.16
  </li>
</ul>

<h2>Changed behavior:</h2>
This section is for behavioral changes to the models that were not due to a bug fix.
<ul>
  <li> The default value of the `Speed` attribute of ConstantSpeedPropagationDelayModel was changed from 300,000,000 m/s to 299,792,458 m/s (speed of light in a vacuum), causing propagation delays using this model to vary slightly.
  </li>
  <li> The LrWpanHelper object was previously instantiating only a LogDistancePropagationLossModel on a SingleModelSpectrumChannel, but no PropagationDelayModel.  The constructor now adds by default a ConstantSpeedPropagationDelayModel.
  </li>
  <li> The Nix-vector routing implementation now uses a lazy flush mechanism,
       which dramatically speeds up the creation of large topologies.
  </li>
</ul>

<hr>
<h1>Changes from ns-3.20 to ns-3.21</h1>
<h2>New API:</h2>
<ul>
  <li> New "const double& SpectrumValue:: operator[] (size_t index) const".
  </li>
  <li> A new TraceSource has been added to TCP sockets: SlowStartThreshold.
  </li>
  <li> New method CommandLine::AddValue (name, attibutePath) to provide a
       shorthand argument "name" for the Attribute "path".  This also has
       the effect of including the help string for the Attribute in the
       Usage message.
  </li>
  <li> The GSoC 2014 project in the LTE module has brought some additional APIs:
    <ul>
      <li>a new abstract class LteFfrAlgorithm, which every future
          implementation of frequency reuse algorithm should inherit from</li>
      <li>a new SAPs: one between MAC Scheduler and FrAlgorithm, one between
	  RRC and FrAlgorithm</li>
      <li>new attribute to enable Uplink Power Control in LteUePhy</li>
      <li>new LteUePowerControl class, an implementation of Uplink Power Control, which is 
          configurable by attributes. ReferenceSignalPower is sent by eNB in SIB2. 
          Uplink Power Control in Closed Loop Accumulative Mode is enabled by default</li>
      <li>seven different Frequency Reuse Algorithms (each has its own attributes): </li>
        <ul>
          <li>LteFrNoOpAlgorithm</li>
          <li>LteFrHardAlgorithm</li>
          <li>LteFrStrictAlgorithm</li>
          <li>LteFrSoftAlgorithm</li>
          <li>LteFfrSoftAlgorithm</li>
          <li>LteFfrEnhancedAlgorithm</li>
          <li>LteFfrDistributedAlgorithm</li>
        </ul>
      <li>attribute in LteFfrAlgorithm to set FrCellTypeId which is used in automatic 
          Frequency Reuse algorithm configuration</li>
      <li>LteHelper has been updated with new methods related to frequency reuse algorithm: 
          SetFfrAlgorithmType and SetFfrAlgorithmAttribute</li>
    </ul>
  </li>
  <li> A new SimpleNetDeviceHelper can now be used to install SimpleNetDevices.
  </li>
  <li> New PacketSocketServer and PacketSocketClient apps, meant to be used in tests.
  </li>
  <li> Tcp Timestamps and Window Scale options have been added and are enabled by default (controllable by attribute).
  </li>
  <li> A new CoDel queue model has been added to the 'internet' module.  
  </li>
  <li> New test macros NS_TEST_ASSERT_MSG_GT_OR_EQ() and NS_TEST_EXPECT_MSG_GT_OR_EQ() have been added.
  </li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
  <li> "Icmpv6L4Protocol::ForgeEchoRequest" is now returning a packet with the proper IPv6 header.
  </li>
  <li> The TCP socket Attribute "SlowStartThreshold" has been renamed "InitialSlowStartThreshold" to
       clarify that the effect is only on the initial value.
  </li>
  <li> all schedulers were updated to interact with FR entity via FFR-SAP. Only PF, PSS, CQA, 
       FD-TBFQ, TD-TBFQ schedulers supports Frequency Reuse functionality. In the beginning 
       of scheduling process, schedulers ask FR entity for available RBGs and then ask if UE 
       can be scheduled on RB</li>
  <li> eNB RRC interacts with FFR entity via RRC-FFR SAP</li>
  <li> new DL-CQI generation approach was implemented. Now DL-CQI is computed from control channel as signal
       and data channel (if received) as interference. New attribute in LteHelper was added to specify 
       DL-CQI generation approach. New approach is default one in LteHelper </li>
  <li> RadioEnvironmentMap can be generated for Data or Control channel and for specified RbId;
       Data or Control channel and RbId can be configured by new attributes in RadioEnvironmentMapHelper </li>
  <li> lte-sinr-chunk-processor refactored to lte-chunk-processor. Removed all lte-xxx-chunk-processor 
       implementations</li>
  <li> BindToNetDevice affects also sockets using IPv6.</li>
  <li> BindToNetDevice now calls implicitly Bind (). To bind a socket to a NetDevice and to a specific address,
       the correct sequence is Bind (address) - BindToNetDevice (device). The opposite will raise an error.</li>
</ul>

<h2>Changes to build system:</h2>
<ul>
<li> None for this release. </li>
</ul>

<h2>Changed behavior:</h2>
<ul>
<li> Behavior will be changed due to the list of bugs fixed (listed in RELEASE_NOTES.md); users are requested to review that list as well.
</ul>

<hr>
<h1>Changes from ns-3.19 to ns-3.20</h1>
<h2>New API:</h2>
<ul>
  <li> Models have been added for low-rate, wireless personal area networks
(LR-WPAN) as specified by IEEE standard 802.15.4 (2006).  The current 
emphasis is on the unslotted mode of 802.15.4 operation for use in Zigbee, 
and the scope is limited to enabling a single mode (CSMA/CA) with basic 
data transfer capabilities. Association with PAN coordinators is not yet 
supported, nor the use of extended addressing. Interference is modeled as 
AWGN but this is currently not thoroughly tested.  The NetDevice Tx queue 
is not limited, i.e., packets are never dropped due to queue becoming full. 
They may be dropped due to excessive transmission retries or channel access 
failure.  </li>
  <li> A new IPv6 routing protocol has been added: RIPng. This protocol is
  an Interior Gateway Protocol and it is available in the Internet module. </li>
  <li> A new LTE MAC downlink scheduling algorithm named Channel and QoS 
  Aware (CQA) Scheduler is provided by the new "ns3::CqaFfMacScheduler" object.
  </li>
  <li> Units may be attached to Time objects, to facilitate specific output
  formats (see Time::As()) </li>
  <li> FlowMonitor "SerializeToXml" functions are now directly available
  from the helper.  </li>
  <li> Access to OLSR's HNA table has been enabled </li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
  <li> The SixLowPan model can now use uncompressed IPv6 headers. An option to
  define the minimum compressed packet size has been added.  </li>
  <li> MinDistance wsa replaced by MinLoss in FriisPropagationLossModel, to
  better handle conditions outside of the assumed far field region. </li>
  <li> In the DSR model, the attribute DsrOptionRerrHeader::ErrorType" has
  been removed. </li>
</ul>

<h2>Changes to build system:</h2>
<ul>
  <li> Python 3.3 is now supported for Python bindings for ns-3.  Python 3.3 
  support for API scanning is not supported.  Python 3.2 is not supported.</li>
  <li>  Enable selection of high precision int64x64_t implementation
  at configure time, for debugging purposes.</li>
  <li> Optimized builds are now enabling signed overflow optimization 
  (-fstrict-overflow) and for gcc 4.8.2 and greater, also warning for cases 
  where an optimizization may occur due to compiler assumption that 
  overflow will not occur. </li>
</ul>

<h2>Changed behavior:</h2>
<ul>
  <li> The Internet FlowMonitor can now track IPv6 packets.  </li>
  <li> Ipv6Extension::m_dropTrace has been removed. Ipv6L3Protocol::m_dropTrace
  is now fired when appropriate.  </li>
  <li> IPv4 identification field value is now dependent on the protocol 
  field.  </li>
  <li> Point-to-point trace sources now contain PPP headers </li>
</ul>

<hr>
<h1>Changes from ns-3.18.1 to ns-3.19</h1>

<h2>New API:</h2>
<ul>
  <li> A new wifi extension for vehicular simulation support is available in the
    src/wave directory.  The current code represents an interim capability to 
    realize an IEEE 802.11p-compliant device, but without the WAVE extensions 
    (which are planned for a later patch).  The WaveNetDevice modelled herein 
    enforces that a WAVE-compliant physical layer (at 5.9 GHz) is selected, and 
    does not require any association between devices (similar to an adhoc WiFi 
    MAC), but is otherwise similar (at this time) to a WifiNetDevice.  WAVE 
    capabililties of switching between control and service channels, or using 
    multiple radios, are not yet modelled.
  </li>
  <li>New SixLowPanNetDevice class providing a shim between 
    IPv6 and real NetDevices. The new module implements 6LoWPAN:
    "Transmission of IPv6 Packets over IEEE 802.15.4 Networks" (see
    <a href="http://www.ietf.org/rfc/rfc4944.txt">RFC 4944</a> and
    <a href="http://www.ietf.org/rfc/rfc6262.txt">RFC 6262</a>), 
    resulting in a heavy header compression for IPv6 packets.
    The module is intended to be used on 802.15.4 NetDevices, but
    it can be used over other NetDevices. See the manual for
    further discussion.
  </li>
  <li> LteHelper has been updated with some new APIs:
    <ul>
      <li>new overloaded Attach methods to enable UE to automatically determine
          the eNodeB to attach to (using initial cell selection);</li>
      <li>new methods related to handover algorithm: SetHandoverAlgorithmType
          and SetHandoverAlgorithmAttribute;</li>
      <li>a new attribute AnrEnabled to activate/deactivate Automatic Neighbour
          Relation (ANR) function; and</li>
      <li>a new method SetUeDeviceAttribute for configuring LteUeNetDevice.</li>
    </ul>
  </li>
  <li> The GSoC 2013 project in the LTE module has brought some additional APIs:
    <ul>
      <li>a new abstract class LteHandoverAlgorithm, which every future
          implementation of automatic handover trigger should inherit from;</li>
      <li>new classes LteHandoverAlgorithm and LteAnr as sub-modules of
          LteEnbNetDevice class; both interfacing with the LteEnbRrc sub-module
          through Handover Management SAP and ANR SAP;</li>
      <li>new attributes in LteEnbNetDevice and LteUeNetDevice classes related
          to Closed Subscriber Group (CSG) functionality in initial cell
          selection;</li>
      <li>new attributes in LteEnbRrc for configuring UE measurements' filtering
          coefficient (i.e., quantity configuration);</li>
      <li>a new public method AddUeMeasReportConfig in LteEnbRrc for setting up
          custom UE measurements' reporting configuration; measurement reports
          can then be captured from the RecvMeasurementReport trace source;
          and</li>
      <li>new trace sources in LteUeRrc to capture more events, such as System
          Information messages (MIB, SIB1, SIB2), initial cell selection, random
          access, and handover.</li>
    </ul>
  </li>
  <li>A new parallel scheduling algorithm based on null messages, a common 
  parallel DES scheduling algorithm, has been added.  The null message 
  scheduler has better scaling properties when running on some scenarios
  with large numbers of nodes since it does not require a global 
  communication.
  </li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
    <li> It is now possible to use Ipv6PacketInfoTag from UDP applications in the
      same way as with Ipv4PacketInfoTag. See Doxygen for current limitations in
  	  using Ipv[4,6]PacketInfoTag to set IP properties.</li>
    <li>A change is introduced for the usage of the EpcHelper
      class. Previously, the EpcHelper class included both the API
      definition and its (only) implementation; as such, users would
      instantiate and use the EpcHelper class directly in their
      simulation programs. From now on,
      EpcHelper is just the base class defining the API, and the
      implementation has been moved to derived classes; as such,
      users are now expected to use one of the derived classes in
      their simulation program. The implementation previously
      provided by the EpcHelper class has been moved to the new
      derived class PointToPointEpcHelper.</li>
  <li> The automatic handover trigger and ANR functions in LTE module have been
    moved from LteEnbRrc class to separate classes. As a result, the related
    attributes, e.g., ServingCellHandoverThreshold, NeighbourCellHandoverOffset,
    EventA2Threshold, and EventA4Threshold have been removed from LteEnbRrc
    class. The equivalent attributes are now in A2A4RsrqHandoverAlgorithm and
    LteAnr classes.</li>
  <li> Master Information Block (MIB) and System Information Block Type 1 (SIB1)
    are now transmitted as LTE control messages, so they are no longer part of
    RRC protocol.</li>
  <li> UE RRC state model in LTE module has been considerably modified and is
    not backward compatible with the previous state model.</li>
  <li> Additional time units (Year, Day, Hour, Minute) were added to the time
  value class that represents simulation time; the largest unit prior to 
  this addition was Second.
  </li>
  <li> SimpleNetDevice and SimpleChannel are not so simple anymore. SimpleNetDevice can be now a
       Broadcast or PointToPoint NetDevice, it can have a limited bandwidth and it uses an output
       queue.       
  </li>
</ul>

<h2>Changes to build system:</h2>

<h2>Changed behavior:</h2>
<ul>
  <li> For the TapBridge device, in UseLocal mode there is a MAC learning function. TapBridge has been waiting for the first packet received from tap interface to set the address of the bridged device to the source address of the first packet. This has caused problems with WiFi.  The new behavior is that after connection to the tap interface, ns-3 learns the MAC address of that interface with a system call and immediately sets the address of the bridged device to the learned one.  See <a href="https://www.nsnam.org/bugzilla/show_bug.cgi?id=1777">bug 1777</a> for more details.</li>
  <li> TapBridge device now correctly implements IsLinkUp() method.</li>
  <li> IPv6 addresses and routing tables are printed like in Linux "route -A inet6" command.</li>
  <li> A change in Ipv[4,6]Interface enforces the correct behaviour of IP 
    when a device do not support the minimum MTU requirements.
    This is set to 68 and 1280 octects respectively.  IP simulations that
    may have run over devices with smaller MTUs than 68 or 1280, respectively,
    will no longer be able to use such devices.</li>
</ul>

<hr>
<h1>Changes from ns-3.18 to ns-3.18.1</h1>
<h2>New API:</h2>
<ul>
  <li> It is now possible to randomize the time of the first beacon from an
  access point.  Use an attribute "EnableBeaconJitter" to enable/disable
  this feature.
  </li>
  <li> A new FixedRoomPositionAllocator helper class is available; it
  allows one to generate a random position uniformly distributed in the
  volume of a chosen room inside a chosen building.
  </li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
  <li> Logging wildcards:  allow "***" as synonym for "*=**" to turn on all logging.
  </li>
  <li> The log component list ("NS_LOG=print-list") is now printed alphabetically.
  </li>
  <li> Some deprecated IEEE 802.11p code has been removed from the wifi module
  </li>
</ul>

<h2>Changes to build system:</h2>
<ul>
  <li> The Python API scanning system (./waf --apiscan) has been fixed (bug 1622)
  </li> 
  <li> Waf has been upgraded from 1.7.11 to 1.7.13
  </li> 
</ul>

<h2>Changed behavior:</h2>
<ul>
  <li> Wifi simulations have additional jitter on AP beaconing (see above) and some bug fixes have been applied to wifi module (see RELEASE_NOTES.md)
  </li>
</ul>

<hr>
<h1>Changes from ns-3.17 to ns-3.18</h1>

<h2>New API:</h2>
<ul>
  <li>New features have been added to the LTE module:
  <ul>
    <li>PHY support for UE measurements (RSRP and RSRQ)</li>
    <li>RRC support for UE measurements (configuration, execution, reporting)</li>
    <li>Automatic Handover trigger based on RRC UE measurement reports</li>
  </ul>
  <li>Data collection components have been added in the 'src/stats' module.
      Data collection includes a Probe class that attaches to ns-3 trace
      sources to filter their output, and two Aggregator classes for 
      marshaling probed data into text files or gnuplot plots.  The ns-3
      tutorial has been extended to illustrate basic functionality. </li>
  <li>In 'src/wifi', several changes were made to enable partial 802.11n support:
    <ul>
      <li>A new helper (HtWifiMacHelper) was added to set up a High Throughput (HT) MAC entity</li>
      <li>New attributes were added to help the user setup a High Throughput (HT) PHY entity. These attributes can be set using the YansWifiPhyHelper</li>
      <li>A new standard value has been added that enables the new 11n data rates.</li>
      <li>New 11n preambles has been added (Mixed format and greenfield). To be able to change Tx duration according to the preamble used, a new class TxVector has been added to carry the transmission parameters (mode, preamble, stbc,..).  Several functions have been updated to allow the passage of TxVector instead of WifiMode in MacLow, WifiRemoteStationManager, WifiPhy, YansWifiPhy,.. </li>
      <li>A new information element has been added:  HTCapabilities. This information element is added to the MAC frame header if the node is an HT node. This HTCapabilites information element is used to advertise the HT capabilities of the node to other nodes in the network</li>
    </ul>
  <li>InternetStackHelper has two new functions:<tt>SetIpv4ArpJitter (bool enable)</tt>
      and <tt>SetIpv6NsRsJitter (bool enable)</tt> to enable/disable
      the random jitter on the tranmission of IPv4 ARP Request and IPv6 NS/RS. </li>
  <li>Bounds on valid time inputs for time attributes can now be enabled.  
      See <tt>attribute-test-suite.cc</tt> for an example.</li>
  <li>New generic hash function interface provided in the simulation core.  
      Two hash functions are provided: murmur3 (default), and the venerable 
      FNV1a.  See the Hash Functions section in the ns-3 manual.</li>
  <li>New Mac16Address has been added. It can be used with IPv6 to make
      an Autoconfigured address.</li>
  <li>Mac64Address support has been extended. It can now be used with 
      IPv6 to make an Autoconfigured address.</li>
  <li>IPv6 can now detect and use Path-MTU. See 
      <tt>examples/ipv6/fragmentation-ipv6-two-MTU.cc</tt> for an example.</li>
  <li>Radvd application has a new Helper. See the updated 
      <tt>examples/ipv6/radvd.cc</tt> for an example.</li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
  <li> The Ipv6InterfaceContainer functions to set a node in forwarding state (i.e., a router) 
  and to install a default router in a group of nodes have been extensively changed.
  The old function <tt>void Ipv6InterfaceContainer::SetRouter (uint32_t i, bool router)</tt>
  is now DEPRECATED.
  </li>
  <li> The documentation's IPv6 addresses (2001:db8::/32, RFC 3849) are now
  dropped by routers.
  </li>
  <li> The 'src/tools' module has been removed, and most files migrated to
  'src/stats'.  For users of these programs (the statistics-processing 
  in average.h, or the gnuplot support), the main change is likely to be
  replacing the inclusion of "tools-module.h" with "stats-module.h".
  Users of the event garbage collector, previously in tools, will now 
  include it from the core module.
  </li>
  <li> The Ipv6 UnicastForwardCallback and  MulticastForwardCallback 
  have a new parameter, the NetDevice the packet has been received from.
  Existing Ipv6RoutingProtocols should update their RouteInput function
  accordingly, e.g., from <tt>ucb (rtentry, p, header);</tt> to <tt>ucb (idev, rtentry, p, header);</tt>
  </li>
  <li> The previous buildings module relied on a specific MobilityModel called
    BuildingsMobilityModel, which supported buildings but only allowed
    static positions. This mobility model has been removed. Now, the
    Buildings module instead relies on a new class called
    MobilityBuildingInfo which can be aggregated to any MobilityModel. This
    allows having moving nodes in presence of buildings with any of
    the existing MobilityModels. 
  </li>
  <li>All functions in WifiRemoteStationManager named GetXxxMode have been changed to GetXxxTxVector </li>
</ul>

<h2>Changes to build system:</h2>
<ul>
  <li> Make references to bug id's in doxygen comments with
    <tt>\bugid{num}</tt>, where <tt>num</tt> is the bug id number.  This
    form will generate a link to the bug in the bug database.
  </li>
</ul>

<h2>Changed behavior:</h2>
<ul>
  <li> Now it is possible to request printing command line arguments to the
desired output stream using PrintHelp or operator &lt;&lt;
<pre>
  CommandLine cmd;
  cmd.Parse (argc, argv);
...

  std::cerr << cmd;
</pre>
or
<pre>
  cmd.PrintHelp (std::cerr);
</pre>
  </li>
  <li>Command line boolean arguments specified with no integer value (e.g. <tt>"--boolArg"</tt>) will toggle the value from the default, instead of always setting the value to true.
  </li>
  <li>IPv4's ARP Request and IPv6's NS/RS are now transmitted with a random delay.
      The delay is, by default, a uniform random variable in time between 0 and 10ms.
      This is aimed at preventing reception errors due to collisions during wifi broadcasts when the sending behavior is synchronized (e.g. due to applications starting at the same time on several different nodes).
      This behaviour can be modified by using ArpL3Protocol's 
      <tt>RequestJitter</tt> and Icmpv6L4Protocol's <tt>SolicitationJitter</tt>
      attributes or by using the new InternetStackHelper functions.
  </li>
  <li>AODV Hellos are disabled by default. The performance with Hellos enabled and disabled are almost identical. With Hellos enabled, AODV will suppress hellos from transmission, if any recent broadcast such as RREQ was transmitted. The attribute <tt>ns3::aodv::RoutingProtocol::EnableHello</tt> can be used to enable/disable Hellos.
</ul>

<hr>
<h1>Changes from ns-3.16 to ns-3.17</h1>

<h2>New API:</h2>
<ul>
  <li>New TCP Westwood and Westwood+ models
  <li>New FdNetDevice class providing a special NetDevice that is able to read
      and write traffic from a file descriptor.  Three helpers are provided
      to associate the file descriptor with different underlying devices:  
    <ul> 
    <li> EmuFdNetDeviceHelper (to associate the |ns3| device with a physical 
         device in the host machine).  This helper is intended to
         eventually replace the EmuNetDevice in src/emu. </li>
    <li> TapFdNetDeviceHelper (to associate the ns-3 device with the file 
         descriptor from a tap device in the host machine) </li>
    <li> PlanteLabFdNetDeviceHelper (to automate the creation of tap devices 
         in PlanetLab nodes, enabling |ns3| simulations that can send and 
         receive traffic though the Internet using PlanetLab resource.</li>
    </ul> 
  </li>
  <li>In Ipv4ClickRouting, the following APIs were added:
    <ul>
      <li>Ipv4ClickRouting::SetDefines(), accessible through ClickInternetStackHelper::SetDefines(), for the user to set Click defines from the ns-3 simulation file.</li>
      <li>SIMCLICK_GET_RANDOM_INT click-to-simulator command for ns-3 to drive Click's random number generation.</li>
    </ul>
  </li>  
  <li>LTE module
    <ul>
      <li> New user-visible LTE API
      <ul>
        <li>Two new methods have been added to LteHelper to enable the X2-based handover functionality: AddX2Interface, which setups the X2 interface between two eNBs, and HandoverRequest, which is  a convenience method that schedules an explicit handover event to be executed at a given point in the simulation. </li>
        <li>the new LteHelper method EnablePhyTraces can now be used to enable the new PHY traces</li>
      </ul>
      </li> 
      <li> New internal LTE API 
      <ul>
        <li>New LTE control message classes DlHarqFeedbackLteControlMessage, 
         RachPreambleLteControlMessage, RarLteControlMessage, MibLteControlMessage</li>
        <li>New class UeManager
        <li>New LteRadioBearerInfo subclasses LteSignalingRadioBearerInfo, 
         LteDataRadioBearerInfo</li>
        <li>New LteSinrChunkProcessor subclasses LteRsReceivedPowerChunkProcessor, 
         LteInterferencePowerChunkProcessor</li>
      </ul>
      </li>
    </ul>
  </li>
  <li>New DSR API
  <ul>
    <li>Added PassiveBuffer class to save maintenance packet entry for passive acknowledgment option</li>
    <li>Added FindSourceEntry function in RreqTable class to keep track of route request entry received from same source node</li>
    <li>Added NotifyDataReciept function in DsrRouting class to notify the data receipt of the next hop from link layer.  This is used for the link layer acknowledgment.</li>
  </ul>
  </li>
  <li>New Tag, PacketSocketTag, to carry the destination address of a packet and the packet type</li>
  <li>New Tag, DeviceNameTag, to carry the ns3 device name from where a packet is coming</li>
  <li>New Error Model, BurstError model, to determine which bursts of packets are errored corresponding to an underlying distribution, burst rate, and burst size</li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
  <li>ns3::Object and subclasses DoStart has been renamed to DoInitialize</li>
  <li>ns3::Object and subclasses Start has been renamed to Initialize</li>
  <li>EnergySource StartDeviceModels renamed to InitializeDeviceModels</li>
  <li>A typo was fixed in an LTE variable name. The variable ns3::AllocationRetentionPriority::preemprionVulnerability was changed to preemptionVulnerability.</li>
  <li>Changes in TestCase API
  <ul>
    <li>TestCase has new enumeration TestDuration containing QUICK, EXTENSIVE, TAKES_FOREVER</li>
    <li>TestCase constructor now requires TestDuration, old constructor marked deprecated</li>
 </ul>
 </li>
  <li>Changes in LTE API
  <ul>
    <li> User-visible LTE API 
    <ul>
      <li>The previous LteHelper method ActivateEpsBearer has been now replaced by two alternative methods: ActivateDataRadioBearer (to be used when the EPC model is not used) and ActivateDedicatedEpsBearer (to be used when the EPC model is used). In the case where the EPC model is used, the default EPS bearer is not automatically activated without the need for a specific method to be called.</li>
    </ul>
    </li> 
    <li> Internal LTE API 
    <ul>
      <li>EpcHelper added methods AddUe, AddX2Interface.  Method AddEnb now requires a cellId.  Signature of ActivateEpsBearer changed to void ActivateEpsBearer (Ptr<NetDevice> ueLteDevice, uint64_t imsi, Ptr<EpcTft> tft, EpsBearer bearer)</li>
      <li>LteHelper added methods EnableDlPhyTraces, EnableUlPhyTraces, EnableDlTxPhyTraces, EnableUlTxPhyTraces, EnableDlRxPhyTraces, EnableUlRxPhyTraces</li>
      <li>LteHelper removed methods EnableDlRlcTraces, EnableUlRlcTraces, EnableDlPdcpTraces, EnableUlPdcpTraces</li>
      <li>RadioBearerStatsCalculator added methods (Set/Get)StartTime, (Set/Get)Epoch, RescheduleEndEpoch, EndEpoch</li>
      <li>RadioBearerStatsCalculator removed methods StartEpoch, CheckEpoch</li>
      <li>RadioBearerStatsCalculator methods UlTxPdu, DlRxPdu now require a cellId</li>
      <li>EpcEnbApplication constructor now requires Ipv4Addresses enbS1uAddress and sgwS1uAddress as well as cellId</li>
      <li>EpcEnbApplication added methods SetS1SapUser, GetS1SapProvider, SetS1apSapMme and GetS1apSapEnb</li>
      <li>EpcEnbApplication removed method ErabSetupRequest</li> 
      <li>EpcSgwPgwApplication added methods SetS11SapMme, GetS11SapSgw, AddEnb, AddUe, SetUeAddress</li>
      <li>lte-common.h new structs PhyTransmissionStatParameters and PhyReceptionStatParameters used in TracedCallbacks</li>
      <li>LteControlMessage new message types DL_HARQ, RACH_PREAMBLE, RAR, MIB</li>
      <li>LteEnbCmacSapProvider new methods RemoveUe, GetRachConfig, AllocateNcRaPreamble, AllocateTemporaryCellRnti</li>
      <li>LteEnbPhy new methods GetLteEnbCphySapProvider, SetLteEnbCphySapUser, GetDlSpectrumPhy, GetUlSpectrumPhy, CreateSrsReport</li>
      <li>LteEnbPhy methods DoSendMacPdu, DoSetTransmissionMode, DoSetSrsConfigurationIndex, DoGetMacChTtiDelay, DoSendLteControlMessage, AddUePhy, DeleteUePhy made private</li>
      <li>LteEnbPhySapProvider removed methods SetBandwidth, SetTransmissionMode, SetSrsConfigurationIndex, SetCellId</li>
      <li>LteEnbPhySapUser added methods ReceiveRachPreamble, UlInfoListElementHarqFeeback, DlInfoListElementHarqFeeback</li>
      <li>LtePdcp added methods (Set/Get)Status</li>
      <li>LtePdcp DoTransmitRrcPdu renamed DoTransmitPdcpSdu</li>
      <li>LteUeRrc new enum State.  New methods SetLteUeCphySapProvider, GetLteUeCphySapUser, SetLteUeRrcSapUser, GetLteUeRrcSapProvider, GetState, GetDlEarfcn, GetDlBandwidth, GetUlBandwidth, GetCellId, SetUseRlcSm .  GetRnti made const.</li> 
      <li>LteUeRrc removed methods ReleaseRadioBearer, GetLcIdVector, SetForwardUpCallback, DoRrcConfigurationUpdateInd</li>
      <li>LtePdcpSapProvider struct TransmitRrcPduParameters renamed TransmitPdcpSduParameters.  Method TransmitRrcPdu renamed TransmitPdcpSdu </li>
      <li>LtePdcpSapUser struct ReceiveRrcPduParameters renamed ReceivePdcpSduParameters.  Method ReceiveRrcPdu renamed TransmitPdcpSdu</li>
      <li>LtePdcpSpecificLtePdcpSapProvider method TransmitRrcPdu renamed TransmitPdcpSdu</li>
      <li>LtePdcpSpecificLtePdcpSapUser method ReceiveRrcPdu  renamed ReceivePdcpSdu. Method ReceiveRrcPdu renamed ReceivePdcpSdu</li>
      <li>LtePhy removed methods DoSetBandwidth and DoSetEarfcn</li>
      <li>LtePhy added methods ReportInterference and ReportRsReceivedPower</li>
      <li>LteSpectrumPhy added methods SetHarqPhyModule, Reset, SetLtePhyDlHarqFeedbackCallback, SetLtePhyUlHarqFeedbackCallback,  AddRsPowerChunkProcessor, AddInterferenceChunkProcessor</li>
      <li>LteUeCphySapProvider removed methods ConfigureRach, StartContentionBasedRandomAccessProcedure, StartNonContentionBasedRandomAccessProcedure</li>
      <li>LteUeMac added method AssignStreams</li>
      <li>LteUeNetDevice methods GetMac, GetRrc, GetImsi  made const</li>
      <li>LteUeNetDevice new method GetNas</li>
      <li>LteUePhy new methods GetLteUeCphySapProvider, SetLteUeCphySapUser, GetDlSpectrumPhy, GetUlSpectrumPhy, ReportInterference, ReportRsReceivedPower, ReceiveLteDlHarqFeedback</li>
      <li>LteUePhy DoSendMacPdu, DoSendLteControlMessage, DoSetTransmissionMode, DoSetSrsConfigurationIndex made private</li>
      <li>LteUePhySapProvider removed methods SetBandwidth, SetTransmissionMode, SetSrsConfigurationIndex</li>
      <li>LteUePhySapProvider added method SendRachPreamble</li>  
    </ul>
   </li>    
  </ul>
  <li>AnimationInterface method EnableIpv4RouteTracking returns reference to calling AnimationInterface object</li>
  <li>To make the API more uniform across the various
  PropagationLossModel classes, the Set/GetLambda methods of the
  FriisPropagationLossModel and TwoRayGroundPropagationLossModel
  classes have been changed to Set/GetFrequency, and now a Frequency
  attribute is exported which replaces the pre-existing Lambda
  attribute. Any previous user code setting a value for Lambda should
  be changed to set instead a value of Frequency = C / Lambda, with C
  = 299792458.0. </li>
</ul>
<h2>Changes to build system:</h2>
<ul>
  <li>Waf shipped with ns-3 has been upgraded to version 1.7.10 and custom
  pkg-config generator has been replaced by Waf's builtin tool.
  </li>
</ul>

<h2>Changed behavior:</h2>
<ul>
  <li>DSR link layer notification has changed.  The model originally used 
  "TxErrHeader" in Ptr<WifiMac> to indicate the transmission
  error of a specific packet in link layer; however, it was not working
  correctly.  The model now uses a different path to implement
  the link layer notification mechanism; specifically, looking into the 
  trace file to find packet receive events.  If the model finds one 
  receive event for the data packet, it is used as the indicator for 
  successful data delivery.</li>
</ul>

<hr>
<h1>Changes from ns-3.15 to ns-3.16</h1>

<h2>New API:</h2>
<ul>
<li>In the Socket class, the following functions were added: 
 <ul>
  <li>(Set/Get)IpTos - sets IP Type of Service field in the IP headers.</li>
  <li>(Set/Is)IpRecvTos - tells the socket to pass information about IP ToS up the stack (by adding SocketIpTosTag to the packet).</li>
  <li>(Set/Get)IpTtl - sets IP Time to live field in the IP headers.</li>
  <li>(Set/Is)RecvIpTtl - tells the socket to pass information about IP TTL up the stack (by adding SocketIpTtlTag to the packet).</li>
  <li>(Set/Is)Ipv6Tclass - sets Traffic Class field in the IPv6 headers.</li>
  <li>(Set/Is)Ipv6RecvTclass - tells the socket to pass information about IPv6 TCLASS up the stack (by adding SocketIpv6TclassTag to the packet).</li>
  <li>(Set/Get)Ipv6HopLimit - sets Hop Limit field in the IPv6 headers.</li>
  <li>(Set/Is)Ipv6RecvHopLimit - tells the socket to pass information about IPv6 HOPLIMIT up the stack (by adding SocketIpv6HoplimitTag to the packet).</li>
 </ul>  
A user can call these functions to set/get the corresponding socket option. See examples/socket/socket-options-ipv4.cc and examples/socket/socket-options-ipv6.cc for examples.
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li>In the MobilityHelper class, the functions EnableAscii () and EnableAsciiAll () were changed to use output stream wrappers rather than standard C++ ostreams. The purpose of this change was to make them behave analogously to other helpers in ns-3 that generate ascii traces.  Now, the file stream that is open in MobilityHelper is closed nicely upon asserts and program exits.</li>
</ul>

<h2>Changes to build system:</h2>
<ul>
<li>It's now possible to use distcc when building ns-3. See tutorial for details.</li>
</ul>

<h2>Changed behavior:</h2>
<ul>
<li>Sending a packet through Ipv4RawSocket now supports checksum in the Ipv4Header. It is still not possible to manually put in arbitrary checksum as the checksum is automatically calculated at Ipv4L3Protocol. The user has to enable checksum globally for this to work. Simply calling Ipv4Header::EnableChecksum() for a single Ipv4Header will not work.</li>
<li>Now MultiModelSpectrumChannel allows a SpectrumPhy instance to change SpectrumModel at runtime by issuing a call to MultiModelSpectrumChannel::AddRx (). Previously, MultiModelSpectrumChannel required each SpectrumPhy instance to stick with the same SpectrumModel for the whole simulation. 
</li>
</ul>

<hr>
<h1>Changes from ns-3.14 to ns-3.15</h1>

<h2>New API:</h2>
<ul>
<li>A RandomVariableStreamHelper has been introduced to assist with 
using the Config subsystem path names to assign fixed stream numbers
to RandomVariableStream objects.</li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li>Derived classes of RandomVariable (i.e. the random variable 
implementations) have been ported to a new RandomVariableStream base class.
<li>For a given distribution DistributionVariable (such as UniformVariable),
the new class name is DistributionRandomVariable (such as 
UniformRandomVariable). </li>
<li>The new implementations are also derived from class ns3::Object and 
are handled using the ns-3 smart pointer (Ptr) class.  </li>
<li>The new variable classes also have a new attributed called "Stream"
which allows them to be assigned to a fix stream index when assigned
to the underlying pseudo-random stream of numbers.</li>
</li>
</ul>

<h2>Changes to build system:</h2>
<ul>
<li></li>
</ul>

<h2>Changed behavior:</h2>
<ul>
<li>Programs using random variables or models that include random variables 
may exhibit changed output for a given run number or seed, due to a possible 
change in the order in which random variables are assigned to underlying 
pseudo-random sequences.  Consult the manual for more information regarding 
this.</li>
</ul>

<hr>
<h1>Changes from ns-3.13 to ns-3.14</h1>

<h2>New API:</h2>
<ul>
<li>The new class AntennaModel provides an API for modeling the radiation pattern of antennas.
</li>
<li>The new buildings module introduces an API (classes, helpers, etc)
  to model the presence of buildings in a wireless network topology. 
</li>
<li>The LENA project's implementation of the LTE Mac Scheduler Interface Specification
   standardized by the Small Cell Forum (formerly Femto Forum) is now available for
  use with the LTE module.
</li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li> The Ipv6RawSocketImpl "IcmpFilter" attribute has been removed. Six 
new member functions have been added to enable the same functionality.
</li>
<li> IPv6 support for TCP and UDP has been implemented.  Socket functions
that take an address [e.g. Send (), Connect (), Bind ()] can accept an
ns3::Ipv6Address or a ns3::Address in addition to taking an ns3::Ipv4Address.
(Note that the ns3::Address must contain a ns3::Ipv6Address or a ns3::Ipv4Address,
otherwise these functions will return an error).
Internally, the socket now stores the remote address as a type "ns3::Address"
instead of a type "ns3::Ipv4Address".  The IPv6 Routing Header extension is not
currently supported in ns3 and will not be reflected in the TCP and UDP checksum
calculations per RFC 2460.  Also note that UDP checksums for IPv6 packets are
required per RFC, but remain optional and disabled by default in ns3 (in the
interest of performance).
</li>
<li>
When calling Bind () on a socket without an address, the behavior remains the
same: it will bind to the IPv4 "any" address (0.0.0.0).  In order to Bind () to
the IPv6 "any" address in a similar fashion, use "Bind6 ()".
</li>
<li>
The prototype for the RxCallback function in the Ipv6EndPoint was changed.
It now includes the destination IPv6 address of the end point which was
needed for TCP.  This lead to a small change in the UDP and ICMPv6 L4
protocols as well.
</li>
<li>
Ipv6RoutingHelper can now print the IPv6 Routing Tables at specific 
intervals or time. Exactly like Ipv4RoutingHelper do.
</li>
<li>
New "SendIcmpv6Redirect" attribute (and getter/setter functions) to 
Ipv6L3Protocol. The behavior is similar to Linux's conf "send_redirects", 
i.e., enable/disable the ICMPv6 Redirect sending.
</li>
<li> The SpectrumPhy abstract class now has a new method
<pre>virtual Ptr&#60;AntennaModel&#62; GetRxAntenna () = 0;</pre>
that all derived classes need to implement in order to integrate properly with the newly added antenna model. In addition, a new member variable "Ptr&#60;AntennaModel&#62; txAntenna" has been added to SpectrumSignalParameters in order to allow derived SpectrumPhy classes to provide information about the antenna model used for the transmission of a waveform.
</li>
<li> The Ns2CalendarScheduler event scheduler has been removed.
</li>
<li>
ErrorUnit enum has been moved into RateErrorModel class, and symbols EU_BIT, EU_BYTE and EU_PKT have been renamed to RateErrorModel::ERROR_UNIT_BIT, RateErrorModel::ERROR_UNIT_BYTE and RateErrorModel::ERROR_UNIT_PACKET. RateErrorModel class attribute "ErrorUnit" values have also been renamed for consistency, and are now "ERROR_UNIT_BIT", "ERROR_UNIT_BYTE", "ERROR_UNIT_PACKET".
</li>
<li>
QueueMode enum from DropTailQueue and RedQueue classes has been unified and moved to Queueu class. Symbols DropTailQueue::PACKETS and DropTailQueue::BYTES are now named Queue::QUEUE_MODE_PACKETS and DropTailQueue::QUEUE_MODE_BYTES. In addition, DropTailQueue and RedQueue class attributes "Mode" have been renamed for consistency from "Packets" and "Bytes" to "QUEUE_MODE_PACKETS" and "QUEUE_MODE_BYTES".
</li>
<li>
The API of the LTE module has undergone a significant redesign with
the merge of the code from the LENA project. The new API is not
backwards compatible with the previous version of the LTE module.
</li>
<li> The Ipv6AddressHelper API has been aligned with the Ipv4AddressHelper API. 
The helper can be set with a call to Ipv6AddressHelper::SetBase 
(Ipv6Address network, Ipv6Prefix prefix) instead of NewNetwork
(Ipv6Address network, Ipv6Prefix prefix).  A new NewAddress (void) method
has been added.  Typical usage will involve calls to SetBase (), NewNetwork (),
and NewAddress (), as in class Ipv4AddressHelper. 
</li>
</ul>

<h2>Changes to build system:</h2>
<ul>
<li> The following files are removed:
<pre>
  src/internet/model/ipv4-l4-protocol.cc
  src/internet/model/ipv4-l4-protocol.h
  src/internet/model/ipv6-l4-protocol.cc
  src/internet/model/ipv6-l4-protocol.h
</pre>
and replaced with:
<pre>
  src/internet/model/ip-l4-protocol.cc
  src/internet/model/ip-l4-protocol.h
</pre>
</li>
</ul>
<h2>Changed behavior:</h2>
<ul>
<li> Dual-stacked IPv6 sockets are implemented.  An IPv6 socket can accept
an IPv4 connection, returning the senders address as an IPv4-mapped address
(IPV6_V6ONLY socket option is not implemented).
</li>
<li>
The following examples/application/helpers were modified to support IPv6:
<pre>
csma-layout/examples/csma-star [*]
netanim/examples/star-animation [*]
point-to-point-layout/model/point-to-point-star.cc
point-to-point-layout/model/point-to-point-grid.cc
point-to-point-layout/model/point-to-point-dumbbell.cc
examples/udp/udp-echo [*]
examples/udp-client-server/udp-client-server [*]
examples/udp-client-server/udp-trace-client-server [*]
applications/helper/udp-echo-helper
applications/model/udp-client
applications/model/udp-echo-client
applications/model/udp-echo-server
applications/model/udp-server
applications/model/udp-trace-client

[*]  Added '--useIpv6' flag to switch between IPv4 and IPv6
</pre>
</li>
</ul>

<hr>
<h1>Changes from ns-3.12 to ns-3.13</h1>

<h2>Changes to build system:</h2>
<ul>
<li> The underlying version of waf used by ns-3 was upgraded to 1.6.7.  
This has a few changes for users and developers:
<ul>
<li> by default, "build" no longer has a subdirectory debug or optimized.  
To get different build directories for different build types, you can use 
the waf configure -o <argument> option, e.g.:
<pre>
  ./waf configure -o shared
  ./waf configure --enable-static -o static
</pre>
</li>
<li> (for developers) the ns3headers taskgen needs to be created with a 
features parameter name:
<pre>
  -  headers = bld.new_task_gen('ns3header')
  +  headers = bld.new_task_gen(features=['ns3header'])
</pre>
<li> no longer need to edit src/wscript to add a module, just create your 
module directory inside src and ns-3 will pick it up
<li> In WAF 1.6, adding -Dxxx options is done via the DEFINES env. var.
instead of CXXDEFINES
<li> waf env values are always lists now, e.g. env['PYTHON'] returns
['/usr/bin/python'], so you may need to add [0] to the value in some places
</ul> 
</ul>

<h2>New API:</h2>
<ul>
<li> In the mobility module, there is a new MobilityModel::GetRelativeSpeed() method returning the relative speed of two objects. </li>
<li> A new Ipv6AddressGenerator class was added to generate sequential
addresses from a provided base prefix and interfaceId.  It also will detect
duplicate address assignments. </li> 
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li> In the spectrum module, the parameters to SpectrumChannel::StartTx () and SpectrumPhy::StartRx () methods are now passed using the new struct SpectrumSignalParameters. This new struct supports inheritance, hence it allows technology-specific PHY implementations to provide technology-specific parameters in SpectrumChannel::StartTx() and SpectrumPhy::StartRx(), while at the same time keeping a set of technology-independent parameters common across all spectrum-enabled PHY implementations (i.e., the duration and the power spectral density which are needed for interference calculation). Additionally, the SpectrumType class has been removed, since now the type of a spectrum signal can be inferred by doing a dynamic cast on SpectrumSignalParameters. See the <A href="http://mailman.isi.edu/pipermail/ns-developers/2011-October/009495.html" >Spectrum API change discussion on ns-developers</A> for the motivation behind this API change.
</li>

<li> The WifiPhyStandard enumerators for specifying half- and quarter-channel 
width standards has had a change in capitalization:
<ul>
<li> WIFI_PHY_STANDARD_80211_10Mhz was changed to WIFI_PHY_STANDARD_80211_10MHZ
<li> WIFI_PHY_STANDARD_80211_5Mhz was changed to WIFI_PHY_STANDARD_80211_5MHZ
</ul>
<li> In the SpectrumPhy base class, the methods to get/set the
  MobilityModel and the NetDevice were previously working with
  opaque Ptr&#60;Object&#62;. Now all these methods have been
  changed so that they work with Ptr&#60;NetDevice&#62;
  and Ptr&#60;MobilityModel&#62; as appropriate. See <A href="https://www.nsnam.org/bugzilla/show_bug.cgi?id=1271">Bug 1271</A> on
  bugzilla for the motivation.
</li>
</ul>

<h2>Changed behavior:</h2>
<ul>
<li> TCP bug fixes
<ul> 
<li> Connection retries count is a separate variable with the retries limit, so cloned sockets can reset the count
<li> Fix bug on RTO that may halt the data flow
<li> Make TCP endpoints always holds the accurate address:port info
<li> RST packet is sent on closed sockets
<li> Fix congestion window sizing problem upon partial ACK in TcpNewReno
<li> Acknowledgement is sent, rather than staying silent, upon arrival of unacceptable packets
<li> Advance TcpSocketBase::m_nextTxSequence after RTO
</ul>
<li> TCP enhancements
<ul>
<li> Latest RTT value now stored in variable TcpSocketBase::m_lastRtt
<li> The list variable TcpL4Protocol::m_sockets now always holds all the created, running TcpSocketBase objects
<li> Maximum announced window size now an attribute, ns3::TcpSocketBase::MaxWindowSize
<li> TcpHeader now recognizes ECE and CWR flags (c.f. RFC3168)
<li> Added TCP option handling call in TcpSocketBase for future extension
<li> Data out of range (i.e. outsize acceptable range of receive window) now computed on bytes, not packets
<li> TCP moves from time-wait state to closed state after twice the time specified by attribute ns3:TcpSocketBase::MaxSegLifeTime
<li> TcpNewReno supports limited transmit (RFC3042) if asserting boolean attribute ns3::TcpNewReno::LimitedTransmit
<li> Nagle's algorithm supported. Default off, turn on by calling TcpSocket::SetTcpNoDelay(true)
</ul>
</ul>

<hr>
<h1>Changes from ns-3.11 to ns-3.12</h1>

<h2>Changes to build system:</h2>
<ul>
</ul>

<h2>New API:</h2>
<ul>
<li> New method, RegularWifiMac::SetPromisc (void), to set the interface
to promiscuous mode.
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li> The spelling of the attribute 'IntialCellVoltage' from LiIonEnergySource 
was corrected to 'InitialCellVoltage'; this will affect existing users who 
were using the attribute with the misspelling.
<li> Two trace sources in class WifiPhy have had their names changed:
<ul> 
<li> 'PromiscSnifferRx' is now 'MonitorSnifferRx'
<li> 'PromiscSnifferTx' is now 'MonitorSnifferTx'
</ul>
</ul>

<h2>Changed behavior:</h2>
<ul>
<li> IPv4 fragmentation is now supported.
</ul>

<hr>
<h1>Changes from ns-3.10 to ns-3.11</h1>

<h2>Changes to build system:</h2>
<ul>
<li><b>Examples and tests are no longer built by default in ns-3</b>
<p>
You can now make examples and tests be built in ns-3 in two ways.
<ol>
<li> Using build.py when ns-3 is built for the first time:
<pre>
    ./build.py --enable-examples --enable-tests
</pre>
<li> Using waf once ns-3 has been built:
<pre>
    ./waf configure --enable-examples --enable-tests
</pre>
</ol>
</p></li>
<li><b> Subsets of modules can be enabled using the ns-3 configuration file</b>
<p>A new configuration file, .ns3rc, has been added to ns-3 that
specifies the modules that should be enabled during the ns-3 build.
See the documentation for details.
</p></li>
</ul>

<h2>New API:</h2>
<ul>
<li><b>int64x64_t</b>
<p>The <b>int64x64_t</b> type implements all the C++ arithmetic operators to behave like one of the
C++ native types. It is a 64.64 integer type which means that it is a 128bit integer type with
64 bits of fractional precision. The existing <b>Time</b> type is now automatically convertible to
<b>int64x64_t</b> to allow arbitrarily complex arithmetic operations on the content of <b>Time</b>
objects. The implementation of <b>int64x64_t</b> is based on the previously-existing
<b>HighPrecision</b> type and supersedes it.
</p></li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li><b>Wifi TX duration calculation moved from InterferenceHelper to WifiPhy</b>
<p>The following static methods have been moved from the InterferenceHelper class to the WifiPhy class:
   <pre>
static Time CalculateTxDuration (uint32_t size, WifiMode payloadMode, enum WifiPreamble preamble);
static WifiMode GetPlcpHeaderMode (WifiMode payloadMode, WifiPreamble preamble);
static uint32_t GetPlcpHeaderDurationMicroSeconds (WifiMode payloadMode, WifiPreamble preamble);
static uint32_t GetPlcpPreambleDurationMicroSeconds (WifiMode payloadMode, WifiPreamble preamble);
static uint32_t GetPayloadDurationMicroSeconds (uint32_t size, WifiMode payloadMode);
</pre>
</p></li>
<li><b>Test cases no longer return a boolean value</b>
<p>Unit test case DoRun() functions no longer return a bool value.  Now, they don't return a value at all.  The motivation for this change was to disallow users from merely returning "true" from a test case to force an error to be recorded.  Instead, test case macros should be used.
</p></li>
<li><b>PhyMac renamed to GenericPhy</b>
<p>The PhyMac interface previously defined in phy-mac.h has been
  renamed to GenericPhy interface and moved to a new file
  generic-phy.h. The related variables and methods have been renamed accordingly. 
</p></li>
<li><b>Scalar</b>
<p>The Scalar type has been removed. Typical code such as:
<pre>
Time tmp = ...;
Time result = tmp * Scalar (5);
</pre>
Can now be rewritten as:
<pre>
Time tmp = ...;
Time result = Time (tmp * 5);
</pre>
</p>
</li>
<li><b>Multicast GetOutputTtl() commands</b>
<p> As part of bug 1047 rework to enable multicast routes on nodes with
more than 16 interfaces, the methods Ipv4MulticastRoute::GetOutputTtl () 
and Ipv6MulticastRoute::GetOutputTtl () have been modified to return
a std::map of interface IDs and TTLs for the route.
</p>
</li>
</ul>

<h2>Changed behavior:</h2>
<ul>
  <li> If the data inside the TCP buffer is less than the available window, TCP tries to ask for more data to the application, in the hope of filling the usable transmission window. In some cases, this change allows sending bigger packets than the previous versions, optimizing the transmission.</li>
  <li> In TCP, the ACK is now processed before invoking any routine that deals with the segment sending, except in case of retransmissions.</li>
</ul>

<hr>
<h1>Changes from ns-3.9 to ns-3.10</h1>

<h2>Changes to build system:</h2>
<ul>
<li><b>Regression tests are no longer run using waf</b>
<p>All regression testing is now being done in test.py.  As a result, a 
separate reference trace repository is no longer needed to perform 
regression tests.  Tests that require comparison against known good traces
can still be run from test.py.  The --regression option for waf has been
removed.  However, the "-r" option to download.py has been kept to 
allow users to fetch older revisions of ns-3 that contain these traces.
</p>
<li><b>Documentation converted to Sphinx</b>
<p> Project documentation (manual, tutorial, and testing) have been
converted to Sphinx from the GNU Texinfo markup format.</p>
</ul>

<h2>New API:</h2>
<ul>
<li><b>Pyviz visualizer</b>  
<p>A Python-based visualizer called pyviz is now integrated with ns-3.
For Python simulations, there is an API to start the visualizer.  You
have to import the visualizer module, and call visualizer.start()
instead of ns3.Simulator.Run().  For C++ simulations, there is no API.
For C++ simulations (but also works for Python ones) you need to set
the GlobalValue SimulatorImplementationType to
"ns3::VisualSimulatorImpl".  This can be set from the command-line,
for example (add the
<tt>--SimulatorImplementationType=ns3::VisualSimulatorImpl</tt>
option), or via the waf option <tt>--visualizer</tt>, in addition to
the usual <tt>--run</tt> option to run programs.
</p></li>

<li><b>WaypointMobility attributes</b>
<p>Two attributes were added to WaypointMobility model:  LazyNotify and
InitialPositionIs Waypoint.  See RELEASE_NOTES.md for details.  </p> </li>

<li><b>802.11g rates for ERP-OFDM added</b>
<p>New WifiModes of the form ErpOfdmRatexxMbps, where xx is the rate
in Mbps (6, 9, 12, 18, 24, 36, 48, 54), are available for 802.11g.  
More details are in the RELEASE_NOTES.md.  </p> </li>

<li><b>Socket::GetSocketType ()</b>
<p>This is analogous to getsockopt(SO_TYPE). ipv4-raw-socket, ipv6-raw-socket,
  and packet-socket return NS3_SOCK_RAW. tcp-socket and nsc-tcp-socket return
  NS3_SOCK_STREAM. udp-socket returns NS3_SOCK_DGRAM.</p></li>

<li><b>BulkSendApplication</b>
<p>Sends data as fast as possible up to MaxBytes or unlimited if MaxBytes is 
zero.  Think OnOff, but without the "off" and without the variable data rate. 
This application only works with NS3_SOCK_STREAM and NS3_SOCK_SEQPACKET sockets, 
for example TCP sockets and not UDP sockets. A helper class exists to 
facilitate creating BulkSendApplications. The API for the helper class 
is similar to existing application helper classes, for example, OnOff.
</p></li>

<li><b>Rakhmatov Vrudhula non-linear battery model</b>
<p>New class and helper for this battery model. </p></li>

<li><b>Print IPv4 routing tables</b>
<p>New class methods and helpers for printing IPv4 routing tables
to an output stream. </p></li>

<li><b>Destination-Sequenced Distance Vector (DSDV) routing protocol</b>
<p>Derives from Ipv4RoutingProtocol and contains a DsdvHelper class. </p></li>

<li><b>3GPP Long Term Evolution (LTE) models</b>
<p>More details are in the RELEASE_NOTES.md. </p></li>

</ul>

<h2>Changes to existing API:</h2>
<ul>
<li><b>Consolidation of Wi-Fi MAC high functionality</b>
<p>Wi-Fi MAC high classes have been reorganised in attempt to
consolidate shared functionality into a single class. This new class
is RegularWifiMac, and it derives from the abstract WifiMac, and is
parent of AdhocWifiMac, StaWifiMac, ApWifiMac, and
MeshWifiInterfaceMac. The QoS and non-QoS class variants are no
longer, with a RegularWifiMac attribute "QosSupported" allowing
selection between these two modes of operation. QosWifiMacHelper and
NqosWifiMacHelper continue to work as previously, with a
behind-the-scenes manipulation of the 'afore-mentioned attribute.
</p></li>

<li><b>New TCP architecture</b>
<p>TcpSocketImpl was replaced by a new base class TcpSocketBase and
several subclasses implementing different congestion control.  From 
a user-level API perspective, the main change is that a new attribute
"SocketType" is available in TcpL4Protocol, to which a TypeIdValue
of a specific Tcp variant can be passed.  In the same class, the attribute 
"RttEstimatorFactory" was also renamed "RttEstimatorType" since it now
takes a TypeIdValue instead of an ObjectFactoryValue.  In most cases, 
however, no change to existing user programs should be needed.
</p></li>
</ul>

<h2>Changed behavior:</h2>
<ul>
<li><b>EmuNetDevice uses DIX instead of LLC encapsulation by default</b>
<p>bug 984 in ns-3 tracker:  real devices don't usually understand LLC/SNAP
so the default of DIX makes more sense.
</p></li>
<li><b>TCP defaults to NewReno congestion control</b>
<p>As part of the TCP socket refactoring, a new TCP implementation provides
slightly different behavior than the previous TcpSocketImpl that provided
only fast retransmit.  The default behavior now is NewReno which provides
fast retransmit and fast recovery with window inflation during recovery.
</p></li>
</ul>

<hr>
<h1>Changes from ns-3.8 to ns-3.9</h1>

<h2>Changes to build system:</h2>

<h2>New API:</h2>
<ul>
<li><b>Wifi set block ack threshold:</b> Two methods for setting block ack
parameters for a specific access class: 
<pre>
void QosWifiMacHelper::SetBlockAckThresholdForAc (enum AccessClass accessClass, uint8_t threshold);
void QosWifiMacHelper::SetBlockAckInactivityTimeoutForAc (enum AccessClass accessClass, uint16_t timeout);
</pre>
</li>
<li><b>Receive List Error Model:</b>  Another basic error model that allows
the user to specify a list of received packets that should be errored.  The
list corresponds not to the packet UID but to the sequence of received
packets as observed by the error model.   See src/common/error-model.h
</li>
<li><b>Respond to interface events:</b> New attribute for Ipv4GlobalRouting,
"RespondToInterfaceEvents", which when enabled, will cause global routes
to be recomputed upon any interface or address notification event from IPv4.
</li>
<li><b>Generic sequence number:</b> New generic sequence number class to 
easily handle comparison, subtraction, etc. for sequence numbers.  
To use it you need to supply two fundamental types as template parameters: 
NUMERIC_TYPE and SIGNED_TYPE.  For instance, <tt>SequenceNumber&lt;uint32_t, int32_t&gt;</tt> 
gives you a 32-bit sequence number, while <tt>SequenceNumber&lt;uint16_t, int16_t&gt;</tt> 
is a 16-bit one.  For your convenience, these are typedef'ed as 
<tt>SequenceNumber32</tt> and <tt>SequenceNumber16</tt>, respectively.
</li>

<li><b>Broadcast socket option:</b> New Socket
methods <tt>SetAllowBroadcast</tt> and <tt>GetAllowBroadcast</tt> add
to NS-3 <tt>Socket</tt>'s the equivalent to the POSIX SO_BROADCAST
socket option (setsockopt/getsockopt).  Starting from this NS-3
version, IPv4 sockets do not allow us to send packets to broadcast
destinations by default; SetAllowBroadcast must be called beforehand
if we wish to send broadcast packets.
</li>

<li><b>Deliver of packet ancillary information to sockets:</b> A method to deliver ancillary information 
to the socket interface (fixed in bug 671):  <pre>void Socket::SetRecvPktInfo (bool flag);</pre>

</ul>

<h2>Changes to existing API:</h2>

<ul>
<li><b>Changes to construction and naming of Wi-Fi transmit rates:</b>
A reorganisation of the construction of Wi-Fi transmit rates has been
undertaken with the aim of simplifying the task of supporting further
IEEE 802.11 PHYs. This work has been completed under the auspices of
Bug 871.

From the viewpoint of simulation scripts not part of the ns-3
distribution, the key change is that WifiMode names of the form
wifi<em>x</em>-<em>n</em>mbs are now invalid. Names now take the
form <em>Cccc</em>Rate<em>n</em>Mbps[BW<em>b</em>MHz],
where <em>n</em> is the root bitrate in megabits-per-second as before
(with only significant figures included, and an underscore replacing
any decimal point), and <em>Cccc</em> is a representation of the
Modulation Class as defined in Table 9-2 of IEEE
Std. 802.11-2007. Currently-supported options for <em>Cccc</em>
are <em>Ofdm</em> and <em>Dsss</em>. For modulation classes where
optional reduced-bandwidth transmission is possible, this is captured
in the final part of the form above, with <em>b</em> specifying the
nominal signal bandwidth in megahertz. </li>

<li><b>Consolidation of classes support Wi-Fi Information Elements:</b>
When the <em>mesh</em> module was introduced it added a class
hierarchy for modelling of the various Information Elements that were
required. In this release, this class hierarchy has extended by moving
the base classes (WifiInformationElement and
WifiInformationElementVector) into the <em>wifi</em> module. This
change is intended to ease the addition of support for modelling of
further Wi-Fi functionality. </li>

<li><b>Changed for {Ipv4,Ipv6}PacketInfoTag delivery:</b> In order to
deliver ancillary information to the socket interface (fixed in bug 671),
<em>Ipv4PacketInfoTag</em> and <em>Ipv6PacketInfoTag</em> are implemented. 
For the delivery of this information, the following changes are made into 
existing class.

In Ipv4EndPoint class,
<pre>
-  void SetRxCallback (Callback&lt;void,Ptr&lt;Packet&gt;, Ipv4Address, Ipv4Address, uint16_t&gt; callback);
+  void SetRxCallback (Callback&lt;void,Ptr&lt;Packet&gt;, Ipv4Header, uint16_t, Ptr&lt;Ipv4Interface&gt; &gt; callback);

-  void ForwardUp (Ptr&lt;Packet&gt; p, Ipv4Address saddr, Ipv4Address daddr, uint16_t sport);
+  void ForwardUp (Ptr&lt;Packet&gt; p, const Ipv4Header& header, uint16_t sport, 
+                  Ptr&lt;Ipv4Interface&gt; incomingInterface);
</pre>
In Ipv4L4Protocol class,
<pre>
   virtual enum RxStatus Receive(Ptr&lt;Packet&gt; p, 
-                                Ipv4Address const &source,
-                                Ipv4Address const &destination,
+                                Ipv4Header const &header,
                                 Ptr&lt;Ipv4Interface&gt; incomingInterface) = 0;
</pre>
<pre>
-Ipv4RawSocketImpl::ForwardUp (Ptr&lt;const Packet&gt; p, Ipv4Header ipHeader, Ptr&lt;NetDevice&gt; device)
+Ipv4RawSocketImpl::ForwardUp (Ptr&lt;const Packet&gt; p, Ipv4Header ipHeader, Ptr&lt;Ipv4Interface&gt; incomingInterface)

-NscTcpSocketImpl::ForwardUp (Ptr&lt;Packet&gt; packet, Ipv4Address saddr, Ipv4Address daddr, uint16_t port)
+NscTcpSocketImpl::ForwardUp (Ptr&lt;Packet&gt; packet, Ipv4Header header, uint16_t port,
+                             Ptr&lt;Ipv4Interface&gt; incomingInterface)

-TcpSocketImpl::ForwardUp (Ptr&lt;Packet&gt; packet, Ipv4Address saddr, Ipv4Address daddr, uint16_t port)
+TcpSocketImpl::ForwardUp (Ptr&lt;Packet&gt; packet, Ipv4Header header, uint16_t port,
+                          Ptr&lt;Ipv4Interface&gt; incomingInterface)

-UdpSocketImpl::ForwardUp (Ptr&lt;Packet&gt; packet, Ipv4Address saddr, Ipv4Address daddr, uint16_t port)
+UdpSocketImpl::ForwardUp (Ptr&lt;Packet&gt; packet, Ipv4Header header, uint16_t port,
+                          Ptr&lt;Ipv4Interface&gt; incomingInterface)

</pre>
  
</li>
<li>The method OutputStreamWrapper::SetStream (std::ostream *ostream) was removed.</li>
)
</ul>

<h2>Changed behavior:</h2>
<ul>
<li><b>Queue trace behavior during Enqueue changed:</b> The behavior of the
Enqueue trace source has been changed to be more intuitive and to agree with
documentation.  Enqueue and Drop events in src/node/queue.cc are now mutually
exclusive.  In the past, the meaning of an Enqueue event was that the Queue
Enqueue operation was being attempted; and this could be followed by a Drop
event if the Queue was full.  The new behavior is such that a packet is either
Enqueue'd successfully or Drop'ped.

<li><b>Drop trace logged for Ipv4/6 forwarding failure:</b> Fixed bug 861; this 
will add ascii traces (drops) in Ipv4 and Ipv6 traces for forwarding failures

<li><b>Changed default WiFi error rate model for OFDM modulation types:</b> 
Adopted more conservative ErrorRateModel for OFDM modulation types (a/g).
This will require 4 to 5 more dB of received power to get similar results
as before, so users may observe a reduced WiFi range when using the defaults.
See tracker issue 944 for more details.
</ul>

<hr>
<h1>Changes from ns-3.7 to ns-3.8</h1>

<h2>Changes to build system:</h2>

<h2>New API:</h2>

<ul>
<li><b>Matrix propagation loss model:</b> This radio propagation model uses a two-dimensional matrix
of path loss indexed by source and destination nodes.

<li><b>WiMAX net device</b>: The developed WiMAX model attempts to provide an accurate MAC and
PHY level implementation of the 802.16 specification with the Point-to-Multipoint (PMP) mode and the WirelessMAN-OFDM 
PHY layer. By adding WimaxNetDevice objects to ns-3 nodes, one can create models of
802.16-based networks. The source code for the WiMAX models lives in the directory src/devices/wimax.
The model is mainly composed of three layers:
<ul>
<li>The convergence sublayer (CS)
<li>The MAC Common Part Sublayer (MAC-CPS)
<li>The Physical layer
</ul>
The main way that users who write simulation scripts will typically
interact with the Wimax models is through the helper API and through
the publicly visible attributes of the model.
The helper API is defined in src/helper/wimax-helper.{cc,h}.
Three examples containing some code that shows how to setup a 802.16 network are located under examples/wimax/ 

<li><b>MPI Interface for distributed simulation:</b> Enables access
to necessary MPI information such as MPI rank and size.

<li><b>Point-to-point remote channel:</b> Enables point-to-point 
connection between net-devices on different simulators, for use 
with distributed simulation.

<li><b>GetSystemId in simulator:</b> For use with distributed 
simulation, GetSystemId returns zero by non-distributed 
simulators.  For the distributed simulator, it returns the 
MPI rank.

<li><b>Enhancements to src/core/random-variable.cc/h:</b> New Zeta random variable generator. The Zeta random 
distribution is tightly related to the Zipf distribution (already in ns-3.7). See the documentation, 
especially because sometimes the Zeta distribution is called Zipf and viceversa. Here we conform to the 
Wikipedia naming convention, i.e., Zipf is bounded while Zeta isn't. 

<li><b>Two-ray ground propagation loss model:</b> Calculates the crossover distance under which Friis is used. The antenna 
height is set to the nodes z coordinate, but can be added to using the model parameter SetHeightAboveZ, which 
will affect ALL stations

<li><b>Pareto random variable</b> has two new constructors to specify scale and shape:
<pre>
ParetoVariable (std::pair<double, double> params);
ParetoVariable (std::pair<double, double> params, double b);
</pre>
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li><b>Tracing Helpers</b>: The organization of helpers for both pcap and ascii
tracing, in devices and protocols, has been reworked.  Instead of each device 
and protocol helper re-implementing trace enable methods, classes have been 
developed to implement user-level tracing in a consistent way; and device and 
protocol helpers use those classes to provide tracing functionality.<br>
In addition to consistent operation across all helpers, the object name service
has been integrated into the trace file naming scheme.<br>
The internet stack helper has been extensively massaged to make it easier to 
manage traces originating from protocols.  It used to be the case that there 
was essentially no opportunity to filter tracing on interfaces, and resulting
trace file names collided with those created by devices.  File names are now
disambiguated and one can enable traces on a protocol/interface basis analogously
to the node/device granularity of device-based helpers.<br>
The primary user-visible results of this change are that trace-related functions
have been changed from static functions to method calls; and a new object has
been developed to hold streams for ascii traces.<br>
New functionality is present for ascii traces.  It is now possible to create
multiple ascii trace files automatically just as was possible for pcap trace 
files.<br>
The implementation of the helper code has been designed also to provide 
functionality to make it easier for sophisticated users to hook traces of 
various kinds and write results to (file) streams.
Before:
<pre>
  CsmaHelper::EnablePcapAll ();

  std::ofstream ascii;
  ascii.open ("csma-one-subnet.tr", std::ios_base::binary | std::ios_base::out);
  CsmaHelper::EnableAsciiAll (ascii);

  InternetStackHelper::EnableAsciiAll (ascii);
</pre>
After:
<pre>
  CsmaHelper csmaHelper;
  InternetStackHelper stack;
  csmaHelper.EnablePcapAll ();

  AsciiTraceHelper ascii;
  csma.EnableAsciiAll (ascii.CreateFileStream ("csma-one-subnet.tr"));

  stack.EnableAsciiIpv4All (stream);
</pre>


<li><b>Serialization and Deserialization</b> in buffer, nix-vector, 
packet-metadata, and packet has been modified to use raw character 
buffers, rather than the Buffer class
<pre>
+ uint32_t Buffer::GetSerializedSize (void) const;
+ uint32_t Buffer::Serialize (uint8_t* buffer, uint32_t maxSize) const;
+ uint32_t Buffer::Deserialize (uint8_t* buffer, uint32_t size); 

- void NixVector::Serialize (Buffer::Iterator i, uint32_t size) const;
+ uint32_t NixVector::Serialize (uint32_t* buffer, uint32_t maxSize) const;
- uint32_t NixVector::Deserialize (Buffer::Iterator i);
+ uint32_t NixVector::Deserialize (uint32_t* buffer, uint32_t size);

- void PacketMetadata::Serialize (Buffer::Iterator i, uint32_t size) const;
+ uint32_t PacketMetadata::Serialize (uint8_t* buffer, uint32_t maxSize) const;
- uint32_t PacketMetadata::Deserialize (Buffer::Iterator i);
+ uint32_t PacketMetadata::Deserialize (uint8_t* buffer, uint32_t size);

+ uint32_t Packet::GetSerializedSize (void) const;
- Buffer Packet::Serialize (void) const;
+ uint32_t Packet::Serialize (uint8_t* buffer, uint32_t maxSize) const;
- void Packet::Deserialize (Buffer buffer);
+ Packet::Packet (uint8_t const*buffer, uint32_t size, bool magic);
</pre>
<li><b>PacketMetadata uid</b> has been changed to a 64-bit value. The 
lower 32 bits give the uid, while the upper 32-bits give the MPI rank 
for distributed simulations. For non-distributed simulations, the 
upper 32 bits are simply zero.
<pre>
- inline PacketMetadata (uint32_t uid, uint32_t size);
+ inline PacketMetadata (uint64_t uid, uint32_t size);
- uint32_t GetUid (void) const;
+ uint64_t GetUid (void) const;
- PacketMetadata::PacketMetadata (uint32_t uid, uint32_t size);
+ PacketMetadata::PacketMetadata (uint64_t uid, uint32_t size); 

- uint32_t Packet::GetUid (void) const;
+ uint64_t Packet::GetUid (void) const;
</pre>

<li><b>Moved propagation models</b> from src/devices/wifi to src/common

<li><b>Moved Mtu attribute from base class NetDevice</b> This attribute is
now found in all NetDevice subclasses.  
</ul>

<h2>Changed behavior:</h2>
<ul>

</ul>

<hr>
<h1>Changes from ns-3.6 to ns-3.7</h1>


<h2>Changes to build system:</h2>

<h2>New API:</h2>

<ul>
<li><b>Equal-cost multipath for global routing:</b> Enables quagga's
equal cost multipath for Ipv4GlobalRouting, and adds an attribute that
can enable it with random packet distribution policy across equal cost routes.
<li><b>Binding sockets to devices:</b> A method analogous to a SO_BINDTODEVICE
socket option has been introduced to class Socket:  <pre>virtual void Socket::BindToNetDevice (Ptr&lt;NetDevice&gt; netdevice);</pre>
<li><b>Simulator event contexts</b>: The Simulator API now keeps track of a per-event
'context' (a 32bit integer which, by convention identifies a node by its id). Simulator::GetContext
returns the context of the currently-executing event while Simulator::ScheduleWithContext creates an
event with a context different from the execution context of the caller. This API is used
by the ns-3 logging system to report the execution context of each log line.
<li><b>Object::DoStart</b>: Users who need to complete their object setup at the start of a simulation
can override this virtual method, perform their adhoc setup, and then, must chain up to their parent.
<li><b>Ad hoc On-Demand Distance Vector (AODV)</b> routing model, 
<a href=http://www.ietf.org/rfc/rfc3561.txt>RFC 3561</a> </li>
<li><b>Ipv4::IsDestinationAddress (Ipv4Address address, uint32_t iif)</b> Method added to support checks of whether a destination address should be accepted 
as one of the host's own addresses.  RFC 1122 Strong/Weak end system behavior can be changed with a new attribute (WeakEsModel) in class Ipv4.  </li>

<li><b>Net-anim interface</b>: Provides an interface to net-anim, a network animator for point-to-point 
links in ns-3.  The interface generates a custom trace file for use with the NetAnim program.</li>

<li><b>Topology Helpers</b>: New topology helpers have been introduced including PointToPointStarHelper, 
PointToPointDumbbellHelper, PointToPointGridHelper, and CsmaStarHelper.</li>

<li><b>IPv6 extensions support</b>: Provides API to add IPv6 extensions and options. Two examples (fragmentation
and loose routing) are available.</li>
</ul>

<h2>Changes to existing API:</h2>
<ul>
<li><b>Ipv4RoutingProtocol::RouteOutput</b> no longer takes an outgoing 
interface index but instead takes an outgoing device pointer; this affects all
subclasses of Ipv4RoutingProtocol.
<pre>
-  virtual Ptr&lt;Ipv4Route&gt; RouteOutput (Ptr&lt;Packet&gt; p, const Ipv4Header &header, uint32_t oif, Socket::SocketErrno &sockerr) = 0;
+  virtual Ptr&lt;Ipv4Route&gt; RouteOutput (Ptr&lt;Packet&gt; p, const Ipv4Header &header, Ptr&lt;NetDevice&gt; oif, Socket::SocketErrno &sockerr) = 0;
</pre>
<li><b>Ipv6RoutingProtocol::RouteOutput</b> no longer takes an outgoing 
interface index but instead takes an outgoing device pointer; this affects all
subclasses of Ipv6RoutingProtocol.
<pre>
-  virtual Ptr&lt;Ipv6Route&gt; RouteOutput (Ptr&lt;Packet&gt; p, const Ipv6Header &header, uint32_t oif, Socket::SocketErrno &sockerr) = 0;
+  virtual Ptr&lt;Ipv6Route&gt; RouteOutput (Ptr&lt;Packet&gt; p, const Ipv6Header &header, Ptr&lt;NetDevice&gt; oif, Socket::SocketErrno &sockerr) = 0;
</pre>
<li><b>Application::Start</b> and <b>Application::Stop</b> have been renamed to
<b>Application::SetStartTime</b> and <b>Application::SetStopTime</b>.
<li><b>Channel::Send</b>: this method does not really exist but each subclass of the Channel
base class must implement a similar method which sends a packet from a node to another node.
Users must now use Simulator::ScheduleWithContext instead of Simulator::Schedule to schedule
the reception event on a remote node.<br>
For example, before:
<pre>
void
SimpleChannel::Send (Ptr&lt;Packet&gt; p, uint16_t protocol, 
         Mac48Address to, Mac48Address from,
         Ptr&lt;SimpleNetDevice&gt; sender)
{
  for (std::vector&lt;Ptr&lt;SimpleNetDevice&gt; &gt;::const_iterator i = m_devices.begin (); i != m_devices.end (); ++i)
    {
      Ptr&lt;SimpleNetDevice&gt; tmp = *i;
      if (tmp == sender)
  {
    continue;
  }
      Simulator::ScheduleNow (&SimpleNetDevice::Receive, tmp, p->Copy (), protocol, to, from);
    }
}
</pre>
After:
<pre>
void
SimpleChannel::Send (Ptr&lt;Packet&gt; p, uint16_t protocol, 
         Mac48Address to, Mac48Address from,
         Ptr&lt;SimpleNetDevice&gt; sender)
{
  for (std::vector&lt;Ptr&lt;SimpleNetDevice&gt; &gt;::const_iterator i = m_devices.begin (); i != m_devices.end (); ++i)
    {
      Ptr&lt;SimpleNetDevice&gt; tmp = *i;
      if (tmp == sender)
  {
    continue;
  }
      Simulator::ScheduleWithContext (tmp->GetNode ()->GetId (), Seconds (0),
                                      &SimpleNetDevice::Receive, tmp, p->Copy (), protocol, to, from);
    }
}
</pre>

<li><b>Simulator::SetScheduler</b>: this method now takes an ObjectFactory
instead of an object pointer directly. Existing callers can trivially be
updated to use this new method.<br>
Before:
<pre>
Ptr&lt;Scheduler&gt; sched = CreateObject&lt;ListScheduler&gt; ();
Simulator::SetScheduler (sched);
</pre>
After:
<pre>
ObjectFactory sched;
sched.SetTypeId ("ns3::ListScheduler");
Simulator::SetScheduler (sched);
</pre>

<li> Extensions to IPv4 <b>Ping</b> application: verbose output and the ability to configure different ping 
sizes and time intervals (via new attributes)

<li><b>Topology Helpers</b>: Previously, topology helpers such as a point-to-point star existed in the 
PointToPointHelper class in the form of a method (ex: PointToPointHelper::InstallStar).  These topology 
helpers have been pulled out of the specific helper classes and created as separate classes.  Several 
different topology helper classes now exist including PointToPointStarHelper, PointToPointGridHelper, 
PointToPointDumbbellHelper, and CsmaStarHelper.  For example, a user wishes to create a 
point-to-point star network:<br>
Before:
<pre>
NodeContainer hubNode;
NodeContainer spokeNodes;
hubNode.Create (1);
Ptr&lt;Node&gt; hub = hubNode.Get (0);
spokeNodes.Create (nNodes - 1);

PointToPointHelper pointToPoint;
pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
NetDeviceContainer hubDevices, spokeDevices;
pointToPoint.InstallStar (hubNode.Get (0), spokeNodes, hubDevices, spokeDevices);
</pre>
After:
<pre>
PointToPointHelper pointToPoint;
pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
PointToPointStarHelper star (nSpokes, pointToPoint);
</pre>

</li>

</ul>

<h2>Changed behavior:</h2>
<ul>
<li> Changed default value of YansWifiPhy::EnergyDetectionThreshold from
-140.0 dBm to -96.0 dBm.  Changed default value of 
YansWifiPhy::CcaModelThreshold from -140.0 dBm to -99.0 dBm.  Rationale
can be found <a href="http://www.nsnam.org/bugzilla/show_bug.cgi?id=689"> 
here</a>.
</li>
<li> Default TTL of IPv4 broadcast datagrams changed from 1 to 64.</li>
<li> Changed DcfManager::UpdateBackoff (): using flooring instead of rounding in calculation of remaining slots. <a href="http://www.nsnam.org/bugzilla/show_bug.cgi?id=695">
  See bug 695.</a></li>
</ul>


<hr>
<h1>Changes from ns-3.5 to ns-3.6</h1>

<h2>Changes to build system:</h2>
<ul>
<li><b>A new test framework is provided with ns-3.6 that primarilay runs outside waf</b>
<p>"./waf check" now runs the new unit tests of the core part of ns-3.6.  
In order to run the complete test package, use "./test.py" which is 
documented in a new manual -- find it in ./doc/testing.  "./waf check"
no longer generates the introspected Doxygen.  Now use "./waf doxygen"
to do this and generate the Doxygen documentation in one step.
</p>
</ul>

<h2>New API:</h2>
<ul>
<li><b>Longest prefix match, support for metrics, for Ipv4StaticRouting and Ipv6StaticRouting</b>
<p>When performing route lookup, first match for longest prefix, and then
based on metrics (default metric = 0).  If metrics are equal, most recent
addition is picked.  Extends API for support of metrics but preserves
backward compatibility.  One small change is that the default route
is no longer stored as index 0 route in the host route table so 
GetDefaultRoute () must be used.
</p>
</li>
<li><b>Route injection for global routing</b>
<p>Add ability to inject and withdraw routes to Ipv4GlobalRouting.  This
allows a user to insert a route and have it redistributed like an OSPF
external LSA to the rest of the topology.
</p>
</li>

<li><b>Athstats</b>
<p>New classes AthstatsWifiTraceSink and AthstatsHelper.
</p>
</li>
<li><b>WifiRemoteStationManager </b>
<p>New trace sources exported by WifiRemoteStationManager: MacTxRtsFailed, MacTxDataFailed, MacTxFinalRtsFailed and MacTxFinalDataFailed.
</p>
</li>

<li><b> IPv6 additions</b>
<p> Add an IPv6 protocol and ICMPv6 capability.
<ul>
<li> new classes Ipv6, Ipv6Interface, Ipv6L3Protocol, Ipv6L4Protocol
<li> Ipv6RawSocket (no UDP or TCP capability yet)
<li> a set of classes to implement Icmpv6, including neighbor discovery,
router solicitation, DAD
<li> new applications Ping6 and Radvd
<li> routing objects Ipv6Route and Ipv6MulticastRoute
<li> routing protocols Ipv6ListRouting and Ipv6StaticRouting
<li> examples: icmpv6-redirect.cc, ping6.cc, radvd.cc, radvd-two-prefix.cc, simple-routing-ping6.cc
</ul>
</p>
</li> 

<li><b>Wireless Mesh Networking models</b>
<ul>
<p>
<li> General multi-interface mesh stack infrastructure (devices/mesh module).
<li> IEEE 802.11s (Draft 3.0) model including Peering Management Protocol and HWMP.
<li> Forwarding Layer for Meshing (FLAME) protocol.
</ul>
</p>
</li>

<li><b>802.11 enhancements</b>
<p>
<ul>
<li> 10MHz and 5MHz channel width supported by 802.11a model (Ramon Bauza and Kirill Andreev).
</ul>
<ul>
<li> Channel switching support. YansWifiPhy can now switch among different channels (Ramon Bauza and Pavel Boyko).
</ul>
</p>
</li>

<li><b> Nix-vector Routing</b>
<p> Add nix-vector routing protocol
<ul>
<li> new helper class Ipv4NixVectorHelper
</ul>
<ul>
<li> examples: nix-simple.cc, nms-p2p-nix.cc
</ul> 
</p>
</li>

<li><b>New Test Framework</b>
<p> Add TestCase, TestSuite classes
<ul>
<li> examples: src/core/names-test-suite.cc, src/core/random-number-test-suite.cc, src/test/ns3tcp/ns3tcp-cwnd-test-suite.cc
</ul> 
</p>
</li>

</ul>

<h2>Changes to existing API:</h2>
<ul>
<li><b>InterferenceHelper</b>
<p>The method InterferenceHelper::CalculateTxDuration (uint32_t size, WifiMode payloadMode, WifiPreamble preamble) has been made static, so that the frame duration depends only on the characteristics of the frame (i.e., the function parameters) and not on the particular standard which is used by the receiving PHY. This makes it now possible to correctly calculate the duration of incoming frames in scenarios in which devices using different PHY configurations coexist in the same channel (e.g., a BSS using short preamble and another BSS using long preamble). </p>
<p> The following member methods have been added to InterferenceHelper:</p>
<pre>
  static WifiMode GetPlcpHeaderMode (WifiMode, WifiPreamble);
  static uint32_t GetPlcpHeaderDurationMicroSeconds (WifiMode, WifiPreamble);
  static uint32_t GetPlcpPreambleDurationMicroSeconds (WifiMode, WifiPreamble);
  static uint32_t GetPayloadDurationMicroSeconds (size, WifiMode); </pre>
<p> The following member methods have been removed from InterferenceHelper:</p>
<pre>
  void Configure80211aParameters (void);
  void Configure80211bParameters (void);
  void Configure80211_10MhzParameters (void);
  void Configure80211_5MhzParameters (void);</pre>
</li>
<li><b>WifiMode</b>
<p>WifiMode now has a WifiPhyStandard attribute which identifies the standard the WifiMode belongs to. To properly set this attribute when creating a new WifiMode, it is now required to explicitly pass a WifiPhyStandard parameter to all WifiModeFactory::CreateXXXX() methods. The WifiPhyStandard value of an existing WifiMode can be retrieved using the new method WifiMode::GetStandard().</p>
</li>
<li><b>NetDevice</b>
<p>In order to have multiple link change callback in NetDevice (i.e. to flush ARP and IPv6 neighbor discovery caches), the following member method has been renamed:</p>
<pre>
- virtual void SetLinkChangeCallback (Callback&lt;void&gt; callback);
+ virtual void AddLinkChangeCallback (Callback&lt;void&gt; callback);</pre>
Now each NetDevice subclasses have a TracedCallback&lt;&gt; object (list of callbacks) instead of Callback&lt;void&gt; ones.
</li>
</ul>

<hr>
<h1>Changes from ns-3.4 to ns-3.5</h1>

<h2>Changes to build system:</h2>
<ul>
</ul>

<h2>New API:</h2>

<ul>
<li><b>YansWifiPhyHelper supporting radiotap and prism PCAP output</b>
<p>The newly supported pcap formats can be adopted by calling the following new method of YansWifiPhyHelper:</p>
<pre>
 +  void SetPcapFormat (enum PcapFormat format);
</pre>
where format is one of PCAP_FORMAT_80211_RADIOTAP, PCAP_FORMAT_80211_PRISM or  PCAP_FORMAT_80211. By default, PCAP_FORMAT_80211 is used, so the default PCAP format is the same as before.</p>
</li>

<li> <b>attributes for class Ipv4</b>
<p> class Ipv4 now contains attributes in ipv4.cc; the first one
is called "IpForward" that will enable/disable Ipv4 forwarding.  
</li>

<li> <b>packet tags</b>
<p>class Packet now contains AddPacketTag, RemovePacketTag and PeekPacketTag 
which can be used to attach a tag to a packet, as opposed to the old 
AddTag method which attached a tag to a set of bytes. The main 
semantic difference is in how these tags behave in the presence of 
fragmentation and reassembly.
</li>

</ul>

<h2>Changes to existing API:</h2>
<ul>

<li><b>Ipv4Interface::GetMtu () deleted</b>
  <p>The Ipv4Interface API is private to internet-stack module; this method
was just a pass-through to GetDevice ()-&gt;GetMtu ().
  </p>
</li>

<li><b>GlobalRouteManager::PopulateRoutingTables () and RecomputeRoutingTables () are deprecated </b>
  <p>This API has been moved to the helper API and the above functions will
be removed in ns-3.6.  The new API is:
<pre>
Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
Ipv4GlobalRoutingHelper::RecomputeRoutingTables ();
</pre>
Additionally, these low-level functions in GlobalRouteManager are now public,
allowing more API flexibility at the low level ns-3 API:
<pre>
GlobalRouteManager::DeleteGlobalRoutes ();
GlobalRouteManager::BuildGlobalRoutingDatabase ();
GlobalRouteManager::InitializeRoutes ();
</pre>
  </p>
</li>

<li><b>CalcChecksum attribute changes</b>
  <p>Four IPv4 CalcChecksum attributes (which enable the computation of 
checksums that are disabled by default) have been collapsed into one global 
value in class Node.  These four calls: 
<pre>
Config::SetDefault ("ns3::Ipv4L3Protocol::CalcChecksum", BooleanValue (true)); 
Config::SetDefault ("ns3::Icmpv4L4Protocol::CalcChecksum", BooleanValue (true));
Config::SetDefault ("ns3::TcpL4Protocol::CalcChecksum", BooleanValue (true));
Config::SetDefault ("ns3::UdpL4Protocol::CalcChecksum", BooleanValue (true));
</pre>
are replaced by one call to:
<pre>
GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));
</pre>
  </p>
</li>

<li><b>CreateObject changes</b>
  <p>CreateObject is now able to construct objects with a non-default constructor.
   If you used to pass attribute lists to CreateObject, you must now use CreateObjectWithAttributes.
  </p>
</li>

<li> <b>packet byte tags renaming</b>
  <ul>
  <li>Packet::AddTag to Packet::AddByteTag</li>
  <li>Packet::FindFirstMatchingTag to Packet::FindFirstMatchingByteTag</li>
  <li>Packet::RemoveAllTags to Packet::RemoveAllByteTags</li>
  <li>Packet::PrintTags to Packet::PrintByteTags</li>
  <li>Packet::GetTagIterator to Packet::GetByteTagIterator</li>
  </ul>
</li>

<li><b>YansWifiPhyHelper::EnablePcap* methods not static any more</b>
<p>To accommodate the possibility of configuring the PCAP format used for wifi promiscuous mode traces, several methods of YansWifiPhyHelper had to be made non-static:
<pre>
-  static void EnablePcap (std::string filename, uint32_t nodeid, uint32_t deviceid);
+         void EnablePcap (std::string filename, uint32_t nodeid, uint32_t deviceid);
-  static void EnablePcap (std::string filename, Ptr&lt;NetDevice&gt; nd);
+         void EnablePcap (std::string filename, Ptr&lt;NetDevice&gt; nd);
-  static void EnablePcap (std::string filename, std::string ndName);
+         void EnablePcap (std::string filename, std::string ndName);
-  static void EnablePcap (std::string filename, NetDeviceContainer d);
+         void EnablePcap (std::string filename, NetDeviceContainer d);
-  static void EnablePcap (std::string filename, NodeContainer n);
+         void EnablePcap (std::string filename, NodeContainer n);
-  static void EnablePcapAll (std::string filename);
+         void EnablePcapAll (std::string filename);
</pre>
</p>
</li>

<li><b>Wifi Promisc Sniff interface modified </b>
<p> 
To accommodate support for the radiotap and prism headers in PCAP traces, the interface for promiscuos mode sniff in the wifi device was changed. The new implementation was heavily inspired by the way the madwifi driver handles monitor mode. A distinction between TX and RX events is introduced, to account for the fact that different information is to be put in the radiotap/prism header (e.g., RSSI and noise make sense only for RX packets). The following are the relevant modifications to the WifiPhy class:
<pre>
-  void NotifyPromiscSniff (Ptr&lt;const Packet&gt; packet);
+  void NotifyPromiscSniffRx (Ptr&lt;const Packet&gt; packet, uint16_t channelFreqMhz, uint32_t rate, bool isShortPreamble, double signalDbm, double noiseDbm);
+  void NotifyPromiscSniffTx (Ptr&lt;const Packet&gt; packet, uint16_t channelFreqMhz, uint32_t rate, bool isShortPreamble);
-  TracedCallback&lt;Ptr&lt;const Packet&gt; &gt; m_phyPromiscSnifferTrace;
+  TracedCallback&lt;Ptr&lt;const Packet&gt;, uint16_t, uint32_t, bool, double, double&gt; m_phyPromiscSniffRxTrace;
+  TracedCallback&lt;Ptr&lt;const Packet&gt;, uint16_t, uint32_t, bool&gt; m_phyPromiscSniffTxTrace;
</pre>
The above mentioned callbacks are expected to be used to call the following method to write Wifi PCAP traces in promiscuous mode:
<pre>
+  void WriteWifiMonitorPacket(Ptr&lt;const Packet&gt; packet, uint16_t channelFreqMhz, uint32_t rate, bool isShortPreamble, bool isTx, double signalDbm, double noiseDbm);
</pre>
In the above method, the isTx parameter is to be used to differentiate between TX and RX packets. For an example of how to implement these callbacks, see the implementation of PcapSniffTxEvent and PcapSniffRxEvent in src/helper/yans-wifi-helper.cc
</p>
</li>

<li><b> Routing decoupled from class Ipv4</b>
<p> All calls of the form "Ipv4::AddHostRouteTo ()" etc. (i.e. to 
add static routes, both unicast and multicast) have been moved to a new 
class Ipv4StaticRouting.  In addition, class Ipv4 now holds only
one possible routing protocol; the previous way to add routing protocols
(by ordered list of priority) has been moved to a new class Ipv4ListRouting.
Class Ipv4 has a new minimal routing API (just to set and get the routing
protocol):
<pre>
-  virtual void AddRoutingProtocol (Ptr&lt;Ipv4RoutingProtocol&gt; routingProtocol, int16_t priority) = 0;
+  virtual void SetRoutingProtocol (Ptr&lt;Ipv4RoutingProtocol&gt; routingProtocol) = 0;
+  virtual Ptr&lt;Ipv4RoutingProtocol&gt; GetRoutingProtocol (void) const = 0;
</pre>
</li>

<li><b> class Ipv4RoutingProtocol is refactored</b>
<p> The abstract base class Ipv4RoutingProtocol has been refactored to
align with corresponding Linux Ipv4 routing architecture, and has been
moved from ipv4.h to a new file ipv4-routing-protocol.h.  The new
methods (RouteOutput () and RouteInput ()) are aligned with Linux 
ip_route_output() and ip_route_input().  However,
the general nature of these calls (synchronous routing lookup for
locally originated packets, and an asynchronous, callback-based lookup
for forwarded packets) is still the same.
<pre>
-  typedef Callback&lt;void, bool, const Ipv4Route&amp;, Ptr&lt;Packet&gt;, const Ipv4Header&amp;&gt; RouteReplyCallback;
+  typedef Callback&lt;void, Ptr&lt;Ipv4Route&gt;, Ptr&lt;const Packet&gt;, const Ipv4Header &amp;&gt; UnicastForwardCallback;
+  typedef Callback&lt;void, Ptr&lt;Ipv4MulticastRoute&gt;, Ptr&lt;const Packet&gt;, const Ipv4Header &amp;&gt; MulticastForwardCallback;
+  typedef Callback&lt;void, Ptr&lt;const Packet&gt;, const Ipv4Header &amp;, uint32_t &gt; LocalDeliverCallback;
+  typedef Callback&lt;void, Ptr&lt;const Packet&gt;, const Ipv4Header &amp;&gt; ErrorCallback;
-  virtual bool RequestInterface (Ipv4Address destination, uint32_t&amp; interface) = 0;
+  virtual Ptr&lt;Ipv4Route&gt; RouteOutput (Ptr&lt;Packet&gt; p, const Ipv4Header &amp;header, uint32_t oif, Socket::SocketErrno &amp;errno) = 0;
-  virtual bool RequestRoute (uint32_t interface,
-                            const Ipv4Header &amp;ipHeader,
-                            Ptr&lt;Packet&gt; packet,
-                            RouteReplyCallback routeReply) = 0;
+  virtual bool RouteInput  (Ptr&lt;const Packet&gt; p, const Ipv4Header &amp;header, Ptr&lt;const NetDevice&gt; idev,
+                             UnicastForwardCallback ucb, MulticastForwardCallback mcb,
+                             LocalDeliverCallback lcb, ErrorCallback ecb) = 0;
</pre>

</li>
<li><b> previous class Ipv4Route, Ipv4MulticastRoute renamed; new classes with
those same names added</b>
<p> The previous class Ipv4Route and Ipv4MulticastRoute are used by 
Ipv4StaticRouting and Ipv4GlobalRouting to record internal routing table
entries, so they were renamed to class Ipv4RoutingTableEntry and
Ipv4MulticastRoutingTableEntry, respectively.  In their place, new
class Ipv4Route and class Ipv4MulticastRoute have been added.  These
are reference-counted objects that are analogous to Linux struct
rtable and struct mfc_cache, respectively, to achieve better compatibility
with Linux routing architecture in the future.  

<li><b> class Ipv4 address-to-interface mapping functions changed</b>
<p>  There was some general cleanup of functions that involve mappings
from Ipv4Address to either NetDevice or Ipv4 interface index.  
<pre>
-  virtual uint32_t FindInterfaceForAddr (Ipv4Address addr) const = 0;
-  virtual uint32_t FindInterfaceForAddr (Ipv4Address addr, Ipv4Mask mask) const = 0;
+  virtual int32_t GetInterfaceForAddress (Ipv4Address address) const = 0;
+  virtual int32_t GetInterfaceForPrefix (Ipv4Address address, Ipv4Mask mask) const = 0;
-  virtual int32_t FindInterfaceForDevice(Ptr&lt;NetDevice&gt; nd) const = 0;
+  virtual int32_t GetInterfaceForDevice (Ptr&lt;const NetDevice&gt; device) const = 0;
-  virtual Ipv4Address GetSourceAddress (Ipv4Address destination) const = 0;
-  virtual bool GetInterfaceForDestination (Ipv4Address dest,
-  virtual uint32_t GetInterfaceByAddress (Ipv4Address addr, Ipv4Mask mask = Ipv4Mask("255.255.255.255"));
</pre>

<li><b> class Ipv4 multicast join API deleted</b>
<p> The following methods are not really used in present form since IGMP
is not being generated, so they have been removed (planned to be replaced
by multicast socket-based calls in the future):

<pre>
- virtual void JoinMulticastGroup (Ipv4Address origin, Ipv4Address group) = 0;
- virtual void LeaveMulticastGroup (Ipv4Address origin, Ipv4Address group) = 0;
</pre>


<li><b>Deconflict NetDevice::ifIndex and Ipv4::ifIndex (bug 85).</b>
<p>All function parameters named "ifIndex" that refer 
to an Ipv4 interface are instead named "interface".
<pre>
- static const uint32_t Ipv4RoutingProtocol::IF_INDEX_ANY = 0xffffffff;
+ static const uint32_t Ipv4RoutingProtocol::INTERFACE_ANY = 0xffffffff;

- bool Ipv4RoutingProtocol::RequestIfIndex (Ipv4Address destination, uint32_t&amp; ifIndex);
+ bool Ipv4RoutingProtocol::RequestInterface (Ipv4Address destination, uint32_t&amp; interface);
(N.B. this particular function is planned to be renamed to RouteOutput() in the
proposed IPv4 routing refactoring)

- uint32_t Ipv4::GetIfIndexByAddress (Ipv4Address addr, Ipv4Mask mask);
+ int_32t Ipv4::GetInterfaceForAddress (Ipv4Address address, Ipv4Mask mask) const;

- bool Ipv4::GetIfIndexForDestination (Ipv4Address dest, uint32_t &amp;ifIndex) const;
+ bool Ipv4::GetInterfaceForDestination (Ipv4Address dest, uint32_t &amp;interface) const;
(N.B. this function is not needed in the proposed Ipv4 routing refactoring)
</pre>


<li><b>Allow multiple IPv4 addresses to be assigned to an interface (bug 188)</b>
  <ul>
  <li> Add class Ipv4InterfaceAddress:  
  This is a new class to resemble Linux's struct in_ifaddr.  It holds IP addressing information, including mask,
  broadcast address, scope, whether primary or secondary, etc.
  <pre>
+  virtual uint32_t AddAddress (uint32_t interface, Ipv4InterfaceAddress address) = 0;
+  virtual Ipv4InterfaceAddress GetAddress (uint32_t interface, uint32_t addressIndex) const = 0;
+  virtual uint32_t GetNAddresses (uint32_t interface) const = 0;
  </pre>
  <li>Regarding legacy API usage, typically where you once did the following,
  using the public Ipv4 class interface (e.g.):
  <pre>
  ipv4A-&gt;SetAddress (ifIndexA, Ipv4Address ("172.16.1.1"));
  ipv4A-&gt;SetNetworkMask (ifIndexA, Ipv4Mask ("255.255.255.255"));
  </pre>
  you now do:
  <pre>
  Ipv4InterfaceAddress ipv4IfAddrA = Ipv4InterfaceAddress (Ipv4Address ("172.16.1.1"), Ipv4Mask ("255.255.255.255"));
  ipv4A-&gt;AddAddress (ifIndexA, ipv4IfAddrA);
  </pre>
  <li> At the helper API level, one often gets an address from an interface
  container.  We preserve the legacy GetAddress (uint32_t i) but it
  is documented that this will return only the first (address index 0)
  address on the interface, if there are multiple such addresses. 
  We provide also an overloaded variant for the multi-address case: 

  <pre>
Ipv4Address Ipv4InterfaceContainer::GetAddress (uint32_t i)
+ Ipv4Address Ipv4InterfaceContainer::GetAddress (uint32_t i, uint32_t j)
  </pre>

  </ul>

<li><b>New WifiMacHelper objects</b>
<p>The type of wifi MAC is now set by two new specific helpers, NqosWifiMacHelper for non QoS MACs and QosWifiMacHelper for Qos MACs. They are passed as argument to WifiHelper::Install methods.</li>
  <pre>
- void WifiHelper::SetMac (std::string type, std::string n0 = "", const AttributeValue &amp;v0 = EmptyAttributeValue (),...)

- NetDeviceContainer WifiHelper::Install (const WifiPhyHelper &amp;phyHelper, NodeContainer c) const
+ NetDeviceContainer WifiHelper::Install (const WifiPhyHelper &amp;phyHelper, const WifiMacHelper &amp;macHelper, NodeContainer c) const

- NetDeviceContainer WifiHelper::Install (const WifiPhyHelper &amp;phy, Ptr&lt;Node&gt; node) const
+ NetDeviceContainer WifiHelper::Install (const WifiPhyHelper &amp;phy, const WifiMacHelper &amp;mac, Ptr&lt;Node&gt; node) const

- NetDeviceContainer WifiHelper::Install (const WifiPhyHelper &amp;phy, std::string nodeName) const
+ NetDeviceContainer WifiHelper::Install (const WifiPhyHelper &amp;phy, const WifiMacHelper &amp;mac, std::string nodeName) const
  </pre>
  See src/helper/nqos-wifi-mac-helper.h and src/helper/qos-wifi-mac-helper.h for more details.
  </p>

<li><b>Remove Mac48Address::IsMulticast</b>
  <p>This method was considered buggy and unsafe to call. Its replacement is Mac48Address::IsGroup.
  </li>

</ul>

<h2>Changed behavior:</h2>
<ul>
</ul>

<hr>
<h1>Changes from ns-3.3 to ns-3.4</h1>

<h2>Changes to build system:</h2>
<ul>
<li>A major option regarding the downloading and building of ns-3 has been
added for ns-3.4 -- the ns-3-allinone feature.  This allows a user to
get the most common options for ns-3 downloaded and built with a minimum
amount of trouble.  See the ns-3 tutorial for a detailed explanation of
how to use this new feature.</li>

<li>The build system now runs build items in parallel by default.  This includes
the regression tests.</li>
</ul>

<h2>New API:</h2>
<ul>
<li>XML support has been added to the ConfigStore in src/contrib/config-store.cc</li>

<li>The ns-2 calendar queue scheduler option has been ported to src/simulator</li>

<li>A ThreeLogDistancePropagationLossModel has been added to src/devices/wifi</li>

<li>ConstantAccelerationMobilityModel in src/mobility/constant-acceleration-mobility-model.h</li>

<li>A new emulation mode is supported with the TapBridge net device (see
src/devices/tap-bridge)</li>

<li>A new facility for naming ns-3 Objects is included (see
src/core/names.{cc,h})</li>

<li>Wifi multicast support has been added in src/devices/wifi</li>
</ul>

<h2>Changes to existing API:</h2>

<ul>
<li>Some fairly significant changes have been made to the API of the
random variable code.  Please see the ns-3 manual and src/core/random-variable.cc
for details.</li>

<li>The trace sources in the various NetDevice classes has been completely
reworked to allow for a consistent set of trace sources across the
devices.  The names of the trace sources have been changed to provide
some context with respect to the level at which the trace occurred.
A new set of trace sources has been added which emulates the behavior
of packet sniffers.  These sources have been used to implement tcpdump-
like functionality and are plumbed up into the helper classes.  The 
user-visible changes are the trace source name changes and the ability
to do promiscuous-mode pcap tracing via helpers.  For further information
regarding these changes, please see the ns-3 manual</li>

<li>StaticMobilityModel has been renamed ConstantPositionMobilityModel
StaticSpeedMobilityModel has been renamed ConstantVelocityMobilityModel</li>

<li>The Callback templates have been extended to support more parameters.
See src/core/callback.h</li>

<li>Many helper API have been changed to allow passing Object-based parameters
as string names to ease working with the object name service.</li>

<li>The Config APIs now accept path segments that are names defined by the
object name service.</li>

<li>Minor changes were made to make the system build under the Intel C++ compiler.</li>

<li>Trace hooks for association and deassociation to/from an access point were
added to src/devices/wifi/nqsta-wifi-mac.cc</li>
</ul>

<h2>Changed behavior:</h2>

<ul>
<li>The tracing system rework has introduced some significant changes in the
behavior of some trace sources, specifically in the positioning of trace sources
in the device code.  For example, there were cases where the packet transmit 
trace source was hit before the packet was enqueued on the device transmit quueue.
This now happens just before the packet is transmitted over the channel medium.
The scope of the changes is too large to be included here.  If you have concerns
regarding trace semantics, please consult the net device documentation for details.
As is usual, the ultimate source for documentation is the net device source code.</li>
</ul>

<hr>
<h1>Changes from ns-3.2 to ns-3.3</h1>

<h2>New API:</h2>
<ul>
<li>
ns-3 ABORT macros in src/core/abort.h
Config::MatchContainer
ConstCast and DynamicCast helper functions for Ptr casting
StarTopology added to several topology helpers
NetDevice::IsBridge () 
</li>

<li>17-11-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/4c1c3f6bcd03">4c1c3f6bcd03</a></li>
<ul>
<li>
The PppHeader previously defined in the point-to-point-net-device code has been 
made public.
</li>
</ul>

<li>17-11-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/16c2970a0344">16c2970a0344</a></li>
<ul>
<li>
An emulated net device has been added as enabling technology for ns-3 emulation
scenarios.  See src/devices/emu and examples/emu-udp-echo.cc for details.
</li>
</ul>

<li>17-11-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/4222173d1e6d">4222173d1e6d</a></li>
<ul>
<li>
Added method InternetStackHelper::EnableAsciiChange to allow allow a user to 
hook ascii trace to the drop trace events in Ipv4L3Protocol and ArpL3Protocol.
</li>
</ul>

</ul>
<h2>Changes to existing API:</h2>
<ul>

<li> NetDevice::MakeMulticastAddress() was renamed to NetDevice::GetMulticast()
and the original GetMulticast() removed </li>

<li> Socket API changes:
<ul>
<li> return type of SetDataSentCallback () changed from bool to void </li>
<li> Socket::Listen() no longer takes a queueLimit argument</li>
</ul>

<li> As part of the Wifi Phy rework, there have been several API changes
at the low level and helper API level.  </li>
<ul>
<li>  At the helper API level, the WifiHelper was split to three classes: 
a WifiHelper, a YansWifiChannel helper, and a YansWifiPhy helper.  Some
functions like Ascii and Pcap tracing functions were moved from class
WifiHelper to class YansWifiPhyHelper. 
<li>  At the low-level API, there have been a number of changes to
make the Phy more modular:</li>
<ul>
<li> composite-propagation-loss-model.h is removed</li>
<li> DcfManager::NotifyCcaBusyStartNow() has changed name</li>
<li> fragmentation related functions (e.g. DcaTxop::GetNFragments()) have
changed API to account for some implementation changes</li>
<li> Interference helper and error rate model added </li>
<li> JakesPropagationLossModel::GetLoss() moved to PropagationLoss() class</li>
<li> base class WifiChannel made abstract </li>
<li> WifiNetDevice::SetChannel() removed </li>
<li> a WifiPhyState helper class added </li>
<li> addition of the YansWifiChannel and YansWifiPhy classes </li>
</ul>
</ul>

<li>17-11-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/dacfd1f07538">dacfd1f07538</a></li>
<ul>
<li>
Change attribute "RxErrorModel" to "ReceiveErrorModel" in CsmaNetDevice for 
consistency between devices.
</li>
</ul>

</ul>
<h2>changed behavior:</h2>
<ul>

<li>17-11-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/ed0dfce40459">ed0dfce40459</a></li>
<ul>
<li>
Relax reasonableness testing in Ipv4AddressHelper::SetBase to allow the 
assignment of /32 addresses.
</li>
</ul>

<li>17-11-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/756887a9bbea">756887a9bbea</a></li>
<ul>
<li>
Global routing supports bridge devices.
</li>
</ul>
</ul>

<hr>
<h1>Changes from ns-3.1 to ns-3.2</h1>

<h2>New API:</h2>
<ul>

<li>26-08-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/5aa65b1ea001">5aa65b1ea001</a></li>
<ul>
<li>
Add multithreaded and real-time simulator implementation.  Allows for emulated
net devices running in threads other than the main simulation thread to schedule
events.  Allows for pacing the simulation clock at 1x real-time.
</li>
</ul>


<li>26-08-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/c69779f5e51e">c69779f5e51e</a></li>
<ul>
<li>
Add threading and synchronization primitives.  Enabling technology for 
multithreaded simulator implementation.
</li>
</ul>

</ul>
<h2>New API in existing classes:</h2>
<ul>

<li>01-08-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/a18520551cdf">a18520551cdf</a></li>
<ul>
<li>class ArpCache has two new attributes:  MaxRetries 
and a Drop trace.  It also has some new public methods but these are 
mostly for internal use.
</ul>
</li>

</ul>
<h2>Changes to existing API:</h2>
<ul>

<li>05-09-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/aa1fb0f43571">aa1fb0f43571</a></li>
<ul>
<li>
Change naming of MTU and packet size attributes in CSMA and Point-to-Point devices<br>
After much discussion it was decided that the preferred way to think about 
the different senses of transmission units and encapsulations was to call the 
MAC MTU simply MTU and to use the overall packet size as the PHY-level attribute
of interest.  See the Doxygen of CsmaNetDevice::SetFrameSize and 
PointToPointNetDevice::SetFrameSize for a detailed description.
</li>
</ul>

<li>25-08-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/e5ab96db540e">e5ab96db540e</a></li>
<ul>
<li>
bug 273: constify packet pointers.<br>
The normal and the promiscuous receive callbacks of the NetDevice API
have been changed from:
<pre>
Callback&lt;bool,Ptr&lt;NetDevice&gt;,Ptr&lt;Packet&gt;,uint16_t,const Address &amp;&gt;
Callback&lt;bool,Ptr&lt;NetDevice&gt;, Ptr&lt;Packet&gt;, uint16_t,
         const Address &amp;, const Address &amp;, enum PacketType &gt;
</pre>
to:
<pre>
Callback&lt;bool,Ptr&lt;NetDevice&gt;,Ptr&lt;const Packet&gt;,uint16_t,const Address &amp;&gt;
Callback&lt;bool,Ptr&lt;NetDevice&gt;, Ptr&lt;const Packet&gt;, uint16_t,
         const Address &amp;, const Address &amp;, enum PacketType &gt;
</pre>
to avoid the kind of bugs reported in 
<a href="http://www.nsnam.org/bugzilla/show_bug.cgi?id=273">bug 273</a>.
Users who implement a subclass of the NetDevice base class need to change the signature
of their SetReceiveCallback and SetPromiscReceiveCallback methods.
</li>
</ul>


<li>04-08-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/cba7b2b80fe8">cba7b2b80fe8</a></li>
<ul>
<li>
Cleanup of MTU confusion and initialization in CsmaNetDevice<br>
The MTU of the CsmaNetDevice defaulted to 65535.  This did not correspond with
the expected MTU found in Ethernet-like devices.  Also there was not clear 
documentation regarding which MTU was being set.  There are two MTU here, one
at the MAC level and one at the PHY level.  We split out the MTU setting to make
this more clear and set the default PHY level MTU to 1500 to be more like
Ethernet.  The encapsulation mode defaults to LLC/SNAP which then puts the
MAC level MTU at 1492 by default.  We allow users to now set the encapsulation
mode, MAC MTU and PHY MTU while keeping the three values consistent.  See the
Doxygen of CsmaNetDevice::SetMaxPayloadLength for a detailed description of the
issues and solution.
</li>
</ul>

<li>21-07-2008; changeset 
<a href="
http://code.nsnam.org/ns-3-dev/rev/99698bc858e8">99698bc858e8</a></li>
<ul>
<li> class NetDevice has added a pure virtual method that
must be implemented by all subclasses:
<pre>
virtual void SetPromiscReceiveCallback (PromiscReceiveCallback cb) = 0;
</pre>
All NetDevices must support this method, and must call this callback
when processing packets in the receive direction (the appropriate place
to call this is device-dependent).  An approach to stub this out
temporarily, if you do not care about immediately enabling this
functionality, would be to add this to your device:
<pre>
void
ExampleNetDevice::SetPromiscReceiveCallback
(NetDevice::PromiscReceiveCallback cb)
{ 
  NS_ASSERT_MSG (false, "No implementation yet for
SetPromiscReceiveCallback");
}
</pre>
To implement this properly, consult the CsmaNetDevice for examples of
when the m_promiscRxCallback is called.
</li>
</ul>

<li>03-07-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/d5f8e5fae1c6">d5f8e5fae1c6</a></li>
<ul>
<li>
Miscellaneous cleanup of Udp Helper API, to fix bug 234
<pre>
class UdpEchoServerHelper
{
public:
- UdpEchoServerHelper ();
- void SetPort (uint16_t port); 
+ UdpEchoServerHelper (uint16_t port);
+ 
+ void SetAttribute (std::string name, const AttributeValue &amp;value);
ApplicationContainer Install (NodeContainer c);

class UdpEchoClientHelper
{
public:
- UdpEchoClientHelper ();
+ UdpEchoClientHelper (Ipv4Address ip, uint16_t port);
- void SetRemote (Ipv4Address ip, uint16_t port);
- void SetAppAttribute (std::string name, const AttributeValue &amp;value);
+ void SetAttribute (std::string name, const AttributeValue &amp;value);
ApplicationContainer Install (NodeContainer c);
</pre>
</li>
</ul>

<li>03-07-2008; changeset 
<a href="
http://code.nsnam.org/ns-3-dev/rev/3cdd9d60f7c7">3cdd9d60f7c7</a></li>
<ul>
<li>
Rename all instances method names using "Set..Parameter" to "Set..Attribute"
(bug 232)
</li>
<li> How to fix your code:  Any use of helper API that was using a method
"Set...Parameter()" should be changed to read "Set...Attribute()".  e.g.
<pre>
- csma.SetChannelParameter ("DataRate", DataRateValue (5000000));
- csma.SetChannelParameter ("Delay", TimeValue (MilliSeconds (2)));
+ csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
+ csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
</pre>
</li>
</ul>
</li>

</ul>
<h2>Changed behavior:</h2>
<ul>

<li>07-09-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/5d836ab1523b">5d836ab1523b</a></li>
<ul>

<li>
Implement a finite receive buffer for TCP<br>
The native TCP model in TcpSocketImpl did not support a finite receive buffer.
This changeset adds the following functionality in this regard:
<ul>
<li>
Being able to set the receiver buffer size through the attributes system.
</li>
<li>
This receiver buffer size is now correctly exported in the TCP header as the
advertised window.  Prior to this changeset, the TCP header advertised window
was set to the maximum size of 2^16 bytes.
window
</li>
<li>
The aforementioned window size is correctly used for flow control, i.e. the
sending TCP will not send more data than available space in the receiver's
buffer.
</li>
<li>
In the case of a receiver window collapse, when a advertised zero-window
packet is received, the sender enters the persist probing state in which
it sends probe packets with one payload byte at exponentially backed-off
intervals up to 60s.  The receiver will continue to send advertised 
zero-window ACKs of the old data so long as the receiver buffer remains full.
When the receiver window clears up due to an application read, the TCP
will finally ACK the probe byte, and update its advertised window appropriately.
</li>
</ul>
See 
<a href="http://www.nsnam.org/bugzilla/show_bug.cgi?id=239"> bug 239 </a> for
more.
</li>
</ul>

<li>07-09-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/7afa66c2b291">7afa66c2b291</a></li>
<ul>
<li>
Add correct FIN exchange behavior during TCP closedown<br>
The behavior of the native TcpSocketImpl TCP model was such that the final
FIN exchange was not correct, i.e. calling Socket::Close didn't send a FIN
packet, and even if it had, the ACK never came back, and even if it had, the
ACK would have incorrect sequence number.  All these various problems have been
addressed by this changeset.  See 
<a href="http://www.nsnam.org/bugzilla/show_bug.cgi?id=242"> bug 242 </a> for
more.
</li>
</ul>

<li> 28-07-2008; changeset 
<a href="http://code.nsnam.org/ns-3-dev/rev/6f68f1044df1">6f68f1044df1</a>
<ul>
<li>
OLSR: HELLO messages hold time changed to 3*hello
interval from hello interval.  This is an important bug fix as
hold time == refresh time was never intentional, as it leads to
instability in neighbor detection.
</ul>
</li>

</ul>

</body>
</html>