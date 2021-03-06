/* Copyright 2013 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "include/instance.h"

#include <QFileInfo>

#include "inisettingsobject.h"
#include "setting.h"
#include "overridesetting.h"

#include "pathutils.h"

Instance::Instance(const QString &rootDir, QObject *parent) :
	QObject(parent)
{
	m_rootDir = rootDir;
	m_settings = new INISettingsObject(configFile(), this);
	
	settings().registerSetting(new Setting("name", "Unnamed Instance"));
	settings().registerSetting(new Setting("iconKey", "default"));
	settings().registerSetting(new Setting("notes", ""));
	settings().registerSetting(new Setting("NeedsRebuild", true));
	settings().registerSetting(new Setting("JarVersion", "Unknown"));
	settings().registerSetting(new Setting("LwjglVersion", "Mojang"));
	settings().registerSetting(new Setting("IntendedJarVersion", ""));
	settings().registerSetting(new Setting("lastLaunchTime", 0));
	
	// Java Settings
	settings().registerSetting(new OverrideSetting("JavaPath", globalSettings->getSetting("JavaPath")));
	settings().registerSetting(new OverrideSetting("JvmArgs", globalSettings->getSetting("JvmArgs")));
	
	// Custom Commands
	settings().registerSetting(new OverrideSetting("PreLaunchCommand", 
												   globalSettings->getSetting("PreLaunchCommand")));
	settings().registerSetting(new OverrideSetting("PostExitCommand", 
												   globalSettings->getSetting("PostExitCommand")));
	
	// Memory
	settings().registerSetting(new OverrideSetting("MinMemAlloc", globalSettings->getSetting("MinMemAlloc")));
	settings().registerSetting(new OverrideSetting("MaxMemAlloc", globalSettings->getSetting("MaxMemAlloc")));
	
	// Auto login
	settings().registerSetting(new OverrideSetting("AutoLogin", globalSettings->getSetting("AutoLogin")));
}

QString Instance::id() const
{
	return QFileInfo(rootDir()).fileName();
}

QString Instance::rootDir() const
{
	return m_rootDir;
}

InstanceList *Instance::instList() const
{
	if (parent()->inherits("InstanceList"))
		return (InstanceList *)parent();
	else
		return NULL;
}

QString Instance::minecraftDir() const
{
	QFileInfo mcDir(PathCombine(rootDir(), "minecraft"));
	QFileInfo dotMCDir(PathCombine(rootDir(), ".minecraft"));
	
	if (dotMCDir.exists() && !mcDir.exists())
        return dotMCDir.filePath();
	else
		return mcDir.filePath();
}

QString Instance::instModsDir() const
{
	return PathCombine(rootDir(), "instMods");
}

QString Instance::binDir() const
{
	return PathCombine(minecraftDir(), "bin");
}

QString Instance::savesDir() const
{
	return PathCombine(minecraftDir(), "saves");
}

QString Instance::mlModsDir() const
{
	return PathCombine(minecraftDir(), "mods");
}

QString Instance::coreModsDir() const
{
	return PathCombine(minecraftDir(), "coremods");
}

QString Instance::resourceDir() const
{
	return PathCombine(minecraftDir(), "resources");
}

QString Instance::screenshotsDir() const
{
	return PathCombine(minecraftDir(), "screenshots");
}

QString Instance::texturePacksDir() const
{
	return PathCombine(minecraftDir(), "texturepacks");
}

QString Instance::mcJar() const
{
	return PathCombine(binDir(), "minecraft.jar");
}

QString Instance::mcBackup() const
{
	return PathCombine(binDir(), "mcbackup.jar");
}

QString Instance::configFile() const
{
	return PathCombine(rootDir(), "instance.cfg");
}

QString Instance::modListFile() const
{
	return PathCombine(rootDir(), "modlist");
}

SettingsObject &Instance::settings() const
{
	return *m_settings;
}
