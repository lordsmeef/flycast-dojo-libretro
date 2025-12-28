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
#include "oslib/oslib.h"
#include "stdclass.h"
#include "file/file_path.h"
#include "archive/rzip.h"
#include "cfg/cfg.h"
#include "cfg/option.h"
#include "emulator.h"
#include "input/gamepad_device.h"
#include "log/LogManager.h"
#include "serialize.h"
#include "dojo/DojoSession.hpp"
#include "rend/gui.h"

#include <libretro.h>
#include <algorithm>
#include <cstdio>
#include <nowide/cstdio.hpp>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 260
#endif

const char *retro_get_system_directory();

extern char game_dir_no_slash[1024];
extern char vmu_dir_no_slash[PATH_MAX];
extern char content_name[PATH_MAX];
extern unsigned per_content_vmus;
extern std::string arcadeFlashPath;
extern retro_environment_t environ_cb;

namespace hostfs
{

std::string getVmuPath(const std::string& port)
{
   char filename[PATH_MAX + 8];

   if ((per_content_vmus == 1 && port == "A1")
		   || per_content_vmus == 2)
   {
      sprintf(filename, "%s.%s.bin", content_name, port.c_str());
      return std::string(vmu_dir_no_slash) + std::string(path_default_slash()) + filename;
   }
   else
   {
      sprintf(filename, "vmu_save_%s.bin", port.c_str());
      return std::string(game_dir_no_slash) + std::string(path_default_slash()) + filename;
   }
}

std::string getArcadeFlashPath()
{
	return arcadeFlashPath;
}

std::string getArcadeFlashPath(std::string suffix)
{
	return arcadeFlashPath + suffix;
}

std::string findFlash(const std::string& prefix, const std::string& names_ro)
{
   std::string root(game_dir_no_slash);
   root += "/";

	char base[512];
	char temp[512];
	char names[512];
	strcpy(names,names_ro.c_str());
	sprintf(base,"%s",root.c_str());

	char* curr=names;
	char* next;
	do
	{
		next=strstr(curr,";");
		if(next) *next=0;
		if (curr[0]=='%')
		{
			sprintf(temp,"%s%s%s",base,prefix.c_str(),curr+1);
		}
		else
		{
			sprintf(temp,"%s%s",base,curr);
		}

		curr=next+1;

		if (path_is_valid(temp))
			return temp;
	} while(next);

	return "";
}

std::string getFlashSavePath(const std::string& prefix, const std::string& name)
{
   std::string root(game_dir_no_slash);

	return root + path_default_slash() + prefix + name;
}

std::string findNaomiBios(const std::string& name)
{
	std::string basepath(game_dir_no_slash);
	return basepath + path_default_slash() + name;
}

std::string getSavestatePath(int index, bool writable)
{
	return get_savestate_file_path(index, writable);
}

std::string getShaderCachePath(const std::string& filename)
{
	return std::string(game_dir_no_slash) + std::string(path_default_slash()) + filename;
}

std::string getTextureLoadPath(const std::string& gameId)
{
	return std::string(retro_get_system_directory()) + "/dc/textures/"
						+ gameId + path_default_slash();
}

std::string getTextureDumpPath()
{
	return std::string(game_dir_no_slash) + std::string(path_default_slash())
			+ "texdump" + std::string(path_default_slash());
}

std::string getBiosFontPath()
{
	return std::string(game_dir_no_slash) + std::string(path_default_slash()) + "font.bin";
}

}

void SaveSettings()
{
	config::Settings::instance().save();
	GamepadDevice::SaveMaplePorts();
}

std::string get_game_name()
{
	std::string state_file = settings.content.path;
	size_t lastindex = state_file.find_last_of('/');
#ifdef _WIN32
	size_t lastindex2 = state_file.find_last_of('\\');
	if (lastindex == std::string::npos)
		lastindex = lastindex2;
	else if (lastindex2 != std::string::npos)
		lastindex = std::max(lastindex, lastindex2);
#endif
	if (lastindex != std::string::npos)
		state_file = state_file.substr(lastindex + 1);
	lastindex = state_file.find_last_of('.');
	if (lastindex != std::string::npos)
		state_file = state_file.substr(0, lastindex);

	return state_file;
}

std::string get_savestate_file_path(int index, bool writable)
{
	std::string state_file = settings.content.path;
	size_t lastindex = state_file.find_last_of('/');
#ifdef _WIN32
	size_t lastindex2 = state_file.find_last_of('\\');
	if (lastindex == std::string::npos)
		lastindex = lastindex2;
	else if (lastindex2 != std::string::npos)
		lastindex = std::max(lastindex, lastindex2);
#endif
	if (lastindex != std::string::npos)
		state_file = state_file.substr(lastindex + 1);
	lastindex = state_file.find_last_of('.');
	if (lastindex != std::string::npos)
		state_file = state_file.substr(0, lastindex);

	if (index == -1)
		state_file = state_file + ".state.net";
	else
	{
		char index_str[4] = "";
		if (index != 0)
			sprintf(index_str, "_%d", index);
		state_file = state_file + index_str + ".state";
	}
	if (writable)
		return get_writable_data_path(state_file);
	return get_readonly_data_path(state_file);
}

std::string get_net_savestate_file_path(bool writable)
{
	std::string path = get_savestate_file_path(0, writable);
	path.append(".net");
	return path;
}

void dc_exit()
{
	INFO_LOG(COMMON, "dc_exit requested (libretro)");
	emu.stop();
}

void dc_savestate(int index)
{
	dc_savestate(index, std::string(""));
}

void dc_savestate(std::string filename)
{
	dc_savestate(0, filename);
}

void dc_savestate(int index, std::string filename)
{
	if (settings.network.online && !config::GGPOEnable)
		return;

	Serializer ser;
	dc_serialize(ser);

	void *data = malloc(ser.size());
	if (data == nullptr)
	{
		WARN_LOG(SAVESTATE, "Failed to save state - could not malloc %d bytes", (int)ser.size());
		gui_display_notification("Save state failed - memory full", 2000);
		return;
	}

	ser = Serializer(data, ser.size());
	dc_serialize(ser);

	if (filename.empty())
		filename = get_savestate_file_path(index, true);

	RZipFile zipFile;
	if (!zipFile.Open(filename, true))
	{
		WARN_LOG(SAVESTATE, "Failed to save state - could not open %s for writing", filename.c_str());
		gui_display_notification("Cannot open save file", 2000);
		free(data);
		return;
	}
	if (zipFile.Write(data, ser.size()) != ser.size())
	{
		WARN_LOG(SAVESTATE, "Failed to save state - error writing %s", filename.c_str());
		gui_display_notification("Error saving state", 2000);
		zipFile.Close();
		free(data);
		return;
	}
	zipFile.Close();

	free(data);
	NOTICE_LOG(SAVESTATE, "Saved state to %s size %d", filename.c_str(), (int)ser.size());
	gui_display_notification("State saved", 1000);
}

void jump_state()
{
	if (dojo.PlayMatch && dojo.replay_version < 2)
	{
		std::string net_save_path = get_savestate_file_path(0, false);
		net_save_path.append(".net");
		dc_loadstate(net_save_path);
	}
	else
	{
		dc_loadstate(config::SavestateSlot);
	}
	emu.start();
}

void dc_loadstate(int index)
{
	dc_loadstate(index, std::string(""));
}

void dc_loadstate(std::string filename)
{
	dc_loadstate(0, filename);
}

void dc_loadstate(int index, std::string filename)
{
	u32 total_size = 0;
	FILE *f = nullptr;

	emu.stop();

	if (filename.empty())
		filename = get_savestate_file_path(index, false);

	RZipFile zipFile;
	if (zipFile.Open(filename, false))
	{
		total_size = (u32)zipFile.Size();
		if (index == -1 && config::GGPOEnable)
		{
			f = zipFile.rawFile();
			long pos = std::ftell(f);
			MD5Sum().add(f)
					.getDigest(settings.network.md5.savestate);
			std::fseek(f, pos, SEEK_SET);
			f = nullptr;
		}
	}
	else
	{
		f = nowide::fopen(filename.c_str(), "rb");

		if (f == nullptr)
		{
			WARN_LOG(SAVESTATE, "Failed to load state - could not open %s for reading", filename.c_str());
			gui_display_notification("Save state not found", 2000);
			return;
		}
		if (index == -1 && config::GGPOEnable)
			MD5Sum().add(f)
					.getDigest(settings.network.md5.savestate);
		std::fseek(f, 0, SEEK_END);
		total_size = (u32)std::ftell(f);
		std::fseek(f, 0, SEEK_SET);
	}

	void *data = malloc(total_size);
	if (data == nullptr)
	{
		WARN_LOG(SAVESTATE, "Failed to load state - could not malloc %d bytes", total_size);
		gui_display_notification("Failed to load state - memory full", 2000);
		if (f != nullptr)
			std::fclose(f);
		else
			zipFile.Close();
		return;
	}

	size_t read_size;
	if (f == nullptr)
	{
		read_size = zipFile.Read(data, total_size);
		zipFile.Close();
	}
	else
	{
		read_size = fread(data, 1, total_size, f);
		std::fclose(f);
	}
	if (read_size != total_size)
	{
		WARN_LOG(SAVESTATE, "Failed to load state - I/O error");
		gui_display_notification("Failed to load state - I/O error", 2000);
		free(data);
		return;
	}

	try {
		Deserializer deser(data, total_size);
		dc_loadstate(deser);
		NOTICE_LOG(SAVESTATE, "Loaded state ver %d from %s size %d", deser.version(), filename.c_str(), total_size);
		if (deser.size() != total_size)
			WARN_LOG(SAVESTATE, "Savestate size %d but only %d bytes used", total_size, (int)deser.size());
	} catch (const Deserializer::Exception& e) {
		ERROR_LOG(SAVESTATE, "%s", e.what());
	}

	free(data);
	EventManager::event(Event::LoadState);
}
