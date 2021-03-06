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

#ifndef INSTVERSIONLIST_H
#define INSTVERSIONLIST_H

#include <QObject>

#include "libmmc_config.h"

class InstVersion;
class Task;

/*!
 * \brief Class that each instance type's version list derives from. 
 * Version lists are the lists that keep track of the available game versions 
 * for that instance. This list will not be loaded on startup. It will be loaded 
 * when the list's load function is called. Before using the version list, you
 * should check to see if it has been loaded yet and if not, load the list.
 */
class LIBMULTIMC_EXPORT InstVersionList : public QObject
{
	Q_OBJECT
public:
	explicit InstVersionList(QObject *parent = 0);
	
	/*!
	 * \brief Gets a task that will reload the version list.
	 * Simply execute the task to load the list.
	 * \return A pointer to a task that reloads the version list.
	 */
	virtual Task *getLoadTask() = 0;
	
	//! Checks whether or not the list is loaded. If this returns false, the list should be loaded.
	virtual bool isLoaded() = 0;
	
	//! Gets the version at the given index.
	virtual const InstVersion *at(int i) const = 0;
	
	//! Returns the number of versions in the list.
	virtual int count() const = 0;
	
	/*!
	 * \brief Finds a version by its descriptor.
	 * \param The descriptor of the version to find.
	 * \return A const pointer to the version with the given descriptor. NULL if
	 * one doesn't exist.
	 */
	virtual const InstVersion *findVersion(const QString &descriptor);
};

#endif // INSTVERSIONLIST_H
