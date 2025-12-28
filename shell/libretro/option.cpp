/*
	Copyright 2021 flyinghead

	This file is part of Flycast.

    Flycast is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Flycast is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Flycast.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "cfg/option.h"
#include "libretro_core_option_defines.h"

namespace config {

// Dynarec

Option<bool> DynarecEnabled("", true);
Option<bool> DynarecIdleSkip("", true);

// General

Option<int> Cable("", 3);									// TV Composite
Option<int> Region(CORE_OPTION_NAME "_region", 1);			// USA
Option<int> Broadcast(CORE_OPTION_NAME "_broadcast", 0);	// NTSC
Option<int> Language(CORE_OPTION_NAME "_language", 1);		// English
Option<bool> FullMMU("");
Option<bool> ForceWindowsCE(CORE_OPTION_NAME "_force_wince");
Option<bool> AutoLoadState("");
Option<bool> AutoSaveState("");
Option<int, false> SavestateSlot("");
Option<bool> ForceFreePlay(CORE_OPTION_NAME "_force_freeplay", true);

// Sound

Option<bool> DSPEnabled(CORE_OPTION_NAME "_enable_dsp", false);
#if HOST_CPU == CPU_ARM
Option<int> AudioBufferSize("", 5644);	// 128 ms
#else
Option<int> AudioBufferSize("", 2822);	// 64 ms
#endif
Option<bool> AutoLatency("");
Option<bool> LimitFPS("", false);

OptionString AudioBackend("", "auto");

// Rendering

RendererOption RendererType;
Option<bool> UseMipmaps(CORE_OPTION_NAME "_mipmapping", true);
Option<bool> Widescreen(CORE_OPTION_NAME "_widescreen_hack");
Option<bool> SuperWidescreen("");
Option<bool> ShowFPS("");
Option<bool> RenderToTextureBuffer(CORE_OPTION_NAME "_enable_rttb");
Option<bool> TranslucentPolygonDepthMask("");
Option<bool> ModifierVolumes(CORE_OPTION_NAME "_volume_modifier_enable", true);
IntOption TextureUpscale(CORE_OPTION_NAME "_texupscale", 1);
IntOption MaxFilteredTextureSize(CORE_OPTION_NAME "_texupscale_max_filtered_texture_size", 256);
Option<float> ExtraDepthScale("", 1.f);
Option<bool> CustomTextures(CORE_OPTION_NAME "_custom_textures");
Option<bool> DumpTextures(CORE_OPTION_NAME "_dump_textures");
Option<int> ScreenStretching("", 100);
Option<bool> Fog(CORE_OPTION_NAME "_fog", true);
Option<bool> FloatVMUs("");
Option<bool> Rotate90("");
Option<bool> PerStripSorting("");
Option<bool> DelayFrameSwapping(CORE_OPTION_NAME "_delay_frame_swapping");
Option<bool> WidescreenGameHacks(CORE_OPTION_NAME "_widescreen_cheats");
std::array<Option<int>, 4> CrosshairColor {
	Option<int>(""),
	Option<int>(""),
	Option<int>(""),
	Option<int>(""),
};
Option<int> SkipFrame(CORE_OPTION_NAME "_frame_skipping");
Option<int> MaxThreads("", 3);
Option<int> AutoSkipFrame(CORE_OPTION_NAME "_auto_skip_frame", 0);
Option<int> RenderResolution("", 480);
Option<bool> VSync("", true);
Option<bool> ThreadedRendering(CORE_OPTION_NAME "_threaded_rendering", false);
Option<int> AnisotropicFiltering(CORE_OPTION_NAME "_anisotropic_filtering");
Option<int> TextureFiltering(CORE_OPTION_NAME "_texture_filtering");
Option<bool> PowerVR2Filter(CORE_OPTION_NAME "_pvr2_filtering");
Option<int64_t> PixelBufferSize("", 512 * 1024 * 1024);
Option<int> FixedFrequency("", 1);
Option<bool> FixedFrequencyThreadSleep("", false);
IntOption PerPixelLayers(CORE_OPTION_NAME "_oit_layers");
Option<bool> NativeDepthInterpolation(CORE_OPTION_NAME "_native_depth_interpolation");
Option<bool> EmulateFramebuffer(CORE_OPTION_NAME "_emulate_framebuffer", false);
Option<bool> FixUpscaleBleedingEdge(CORE_OPTION_NAME "_fix_upscale_bleeding_edge", true);

// Misc

Option<bool> SerialConsole("");
Option<bool> SerialPTY("");
Option<bool> UseReios(CORE_OPTION_NAME "_hle_bios");

Option<bool> OpenGlChecks("", false);
Option<bool> FastGDRomLoad(CORE_OPTION_NAME "_gdrom_fast_loading", false);

Option<std::vector<std::string>, false> ContentPath("");
//Option<bool, false> HideLegacyNaomiRoms("", true);

// Network

Option<bool> NetworkEnable("", false);
Option<bool> ActAsServer(CORE_OPTION_NAME "_ggpo_role", false);
OptionString DNS("", "46.101.91.123");
OptionString NetworkServer(CORE_OPTION_NAME "_ggpo_remote_ip", "127.0.0.1");
Option<int> LocalPort("", 0);
Option<bool> EmulateBBA(CORE_OPTION_NAME "_emulate_bba", false);
Option<bool> EnableUPnP(CORE_OPTION_NAME "_upnp", false);
Option<bool> GGPOEnable(CORE_OPTION_NAME "_ggpo_enable", false);
Option<int> GGPOPort(CORE_OPTION_NAME "_ggpo_port", 19713);
Option<int> GGPODelay(CORE_OPTION_NAME "_ggpo_delay", 0);
Option<bool> NetworkStats(CORE_OPTION_NAME "_ggpo_stats_overlay", true);
Option<int> GGPOAnalogAxes(CORE_OPTION_NAME "_ggpo_analog_axes", 0);
Option<int> GGPORemotePort(CORE_OPTION_NAME "_ggpo_remote_port", 19713);
Option<bool> GGPOChat("", true);
Option<bool> GGPOChatTimeoutToggle("", true);
Option<bool> GGPOChatTimeoutToggleSend("", false);
Option<int> GGPOChatTimeout("", 10);
Option<bool> NetworkOutput(CORE_OPTION_NAME "_network_output", false);
Option<bool> EnableWinFWPolicy("", true);

// Dojo

Option<bool> DojoEnable("", false);
Option<bool> DojoActAsServer("", true);
Option<bool> RecordMatches("", false);
Option<bool> Spectating("", false);
Option<bool> Transmitting("", true);
Option<bool> ServiceTransmitOnly("", true);
Option<bool> Receiving("", false);
OptionString DojoServerIP("", "127.0.0.1");
OptionString DojoServerPort("", "6000");
Option<int> Delay("", 0);
Option<int> Debug("", 8);
OptionString ReplayFilename("", "");
Option<int> PacketsPerFrame("", 3);
Option<bool> EnableBackfill("", true);
Option<int> NumBackFrames("", 3);
Option<bool> EnableLobby("", false);
OptionString PlayerName("", "Player");
OptionString OpponentName("", "Opponent");
Option<bool> TestGame("", false);
OptionString SpectatorIP("", "match.dojo.ooo");
OptionString SpectatorPort("", "7000");
OptionString LobbyMulticastAddress("", "224.1.10.1");
OptionString LobbyMulticastPort("", "52001");
Option<bool> EnableMatchCode("", true);
OptionString MatchmakingServerAddress("", "match.dojo.ooo");
OptionString MatchmakingServerPort("", "52001");
OptionString MatchCode("", "");
OptionString GameName("", "");
Option<bool> EnableMemRestore("", false);
OptionString DojoProtoCall("", "");
Option<bool> EnablePlayerNameOverlay("", true);
Option<bool> IgnoreNetSave("", false);
Option<bool> NetCustomVmu("", false);
Option<bool> ShowPlaybackControls("", true);
Option<int> RxFrameBuffer("", 1800);
Option<bool> LaunchReplay("", false);
Option<bool> Training("", false);
Option<bool> EnableSessionQuickLoad("", false);
OptionString Quark("", "");
Option<bool> PlayerSwitched("", false);
OptionString NetplayMethod("", "GGPO");
OptionString NetSaveBase("", "https://github.com/blueminder/flycast-netplay-savestates/raw/main/");
Option<bool> NetStartVerifyRoms("", false);
Option<bool> ShowPublicIP("", false);
Option<bool> ShowInputDisplay("", true);
Option<bool> ShowReplayInputDisplay("", false);
Option<bool> UseAnimeInputNotation("", false);
Option<bool> HideRandomInputSlot("", true);
Option<bool> BufferAutoResume("", true);
Option<bool> RecordOnFirstInput("", false);
Option<bool> ForceRealBios("", false);
Option<bool> OutputStreamTxt("", false);
OptionString UpdateChannel("", "stable");
Option<bool> ShowTrainingGameOverlay("", true);
Option<bool> EnableTrainingLua("", true);

Option<int> EnableMouseCaptureToggle("", false);
Option<bool> EnableDiagonalCorrection("", false);
Option<int> SOCDResolution("", 1);

Option<int> FirstTo("", 0);
Option<bool> TransmitScore("", false);

OptionString SpectateKey("", "");
Option<bool> Relay("", false);
OptionString RelayKey("", "");
Option<int> DefaultRelayPort("", 8001);
OptionString RelayAddressHistory("", "");

Option<bool> HostJoinSelect("", false);
Option<bool> HideKey("", false);

Option<bool> CopyMissingSharedMem("", true);

Option<int, false> RecSlotFile("");
Option<bool> MultiOutputStreamTxt("", false);
Option<int> MultiOutputStreamTxtMax("", 4);
Option<int> MultiOutputStreamTxtIdx("", 4);
Option<bool> CustomOutputStreamTxt("", false);

// Maple

Option<int> MouseSensitivity("", 100);
Option<int> VirtualGamepadVibration("", 20);

std::array<Option<MapleDeviceType>, 4> MapleMainDevices {
	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),
};
std::array<std::array<Option<MapleDeviceType>, 2>, 4> MapleExpansionDevices {
	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),

	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),

	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),

	Option<MapleDeviceType>("", MDT_None),
	Option<MapleDeviceType>("", MDT_None),
};

} // namespace config
