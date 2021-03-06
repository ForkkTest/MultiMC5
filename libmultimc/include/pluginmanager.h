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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QList>
#include <QPluginLoader>

#include "libmmc_config.h"

/*!
 * \brief This class is a singleton that manages loading plugins.
 */
class LIBMULTIMC_EXPORT PluginManager : public QObject
{
	Q_OBJECT
public:
	/*!
	 * \brief Gets the plugin manager instance.
	 */
	static PluginManager &get() { return manager; }
	
	/*!
	 * \brief Loads plugins from the given directory.
	 * This function does \e not initialize the plugins. It simply loads their
	 * classes. Use the init functions to initialize the various plugin types.
	 * \param The directory to load plugins from.
	 * \return True if successful. False on failure.
	 */
	bool loadPlugins(QString pluginDir);
	
	/*!
	 * \brief Checks how many plugins are loaded.
	 * \return The number of plugins.
	 */
	int count() { return m_plugins.count(); }
	
	/*!
	 * \brief Gets the plugin at the given index.
	 * \param index The index of the plugin to get.
	 * \return The plugin at the given index.
	 */
	QPluginLoader *getPlugin(int index);
	
	/*!
	 * \brief Initializes and registers all the instance types. 
	 * This is done by going through the plugin list and registering all of the
	 * plugins that derive from the InstanceTypeInterface with the InstanceLoader.
	 */
	void initInstanceTypes();
	
private:
	PluginManager();
	
	QList<QPluginLoader *> m_plugins;
	
	static PluginManager manager;
};

#endif // PLUGINMANAGER_H
