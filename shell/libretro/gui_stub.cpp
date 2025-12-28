// Libretro builds don't link the ImGui-based GUI; provide minimal no-op stubs.
#include "rend/gui.h"

#include <string>

GuiState gui_state = GuiState::Closed;
bool game_started = false;
std::string error_msg;

void gui_init()
{
	gui_state = GuiState::Closed;
}

void gui_initFonts()
{
}

void gui_open_pause()
{
	if (gui_state == GuiState::ReplayPause)
		gui_state = GuiState::Closed;
	else
		gui_state = GuiState::ReplayPause;
}

void gui_open_step()
{
}

void gui_open_settings()
{
	gui_state = GuiState::Settings;
}

void gui_display_ui()
{
}

void gui_display_osd()
{
}

void gui_display_profiler()
{
}

void gui_open_onboarding()
{
	gui_state = GuiState::Onboarding;
}

void gui_term()
{
	gui_state = GuiState::Closed;
}

void gui_cancel_load()
{
}

void gui_refresh_files()
{
}

void gui_cheats()
{
}

void gui_keyboard_input(u16 /*wc*/)
{
}

void gui_keyboard_inputUTF8(const std::string& /*s*/)
{
}

void gui_keyboard_key(u8 /*keyCode*/, bool /*pressed*/, u8 /*modifiers*/)
{
}

bool gui_keyboard_captured()
{
	return false;
}

bool gui_mouse_captured()
{
	return false;
}

void gui_set_mouse_position(int /*x*/, int /*y*/)
{
}

void gui_set_mouse_button(int /*button*/, bool /*pressed*/)
{
}

void gui_set_mouse_wheel(float /*delta*/)
{
}

void gui_set_insets(int /*left*/, int /*right*/, int /*top*/, int /*bottom*/)
{
}

void gui_stop_game(const std::string& /*message*/)
{
	game_started = false;
	gui_state = GuiState::Closed;
}

void gui_start_game(const std::string& /*path*/)
{
	game_started = true;
	gui_state = GuiState::Closed;
}

void gui_error(const std::string& what)
{
	error_msg = what;
}

void gui_setOnScreenKeyboardCallback(void (*/*callback*/)(bool /*show*/))
{
}

void gui_save()
{
}

void gui_open_host_wait()
{
	gui_state = GuiState::HostWait;
}

void gui_open_guest_wait()
{
	gui_state = GuiState::GuestWait;
}

void gui_open_disconnected()
{
	gui_state = GuiState::Disconnected;
}

void gui_open_ggpo_join()
{
	gui_state = GuiState::GGPOJoin;
}

void gui_open_relay_join()
{
	gui_state = GuiState::RelayJoin;
}

void gui_open_relay_select()
{
	gui_state = GuiState::RelaySelect;
}

void scanner_stop()
{
}

void scanner_refresh()
{
}
