// Copyright (c) 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef IOX_HOOFS_POSIX_WRAPPER_COMMAND_LINE_INL
#define IOX_HOOFS_POSIX_WRAPPER_COMMAND_LINE_INL

#include "iceoryx_hoofs/posix_wrapper/command_line.hpp"

namespace iox
{
namespace posix
{
namespace internal
{
template <typename T>
inline T OptionManager::extractOptionArgumentValue(const CommandLineOption& options,
                                                   const char shortName,
                                                   const CommandLineOption::Name_t& name)
{
    if (shortName != CommandLineOptionSet::NO_SHORT_OPTION)
    {
        return options.get<T>(CommandLineOption::Name_t{cxx::TruncateToCapacity, &shortName, 1})
            .or_else([this](auto&) { handleError(); })
            .value();
    }
    else
    {
        return options.get<T>(name).or_else([this](auto&) { handleError(); }).value();
    }
}

template <typename T>
inline T OptionManager::defineOption(T& referenceToMember,
                                     const char shortName,
                                     const CommandLineOption::Name_t& name,
                                     const CommandLineOptionSet::Description_t& description,
                                     const OptionType optionType,
                                     T defaultArgumentValue)
{
    m_optionSet.addOption(CommandLineOptionSet::Entry{
        shortName,
        name,
        description,
        optionType,
        {cxx::TypeInfo<T>::NAME},
        CommandLineOption::Argument_t(cxx::TruncateToCapacity, cxx::convert::toString(defaultArgumentValue))});

    m_assignments.emplace_back([this, &referenceToMember, shortName, name](CommandLineOption& options) {
        referenceToMember = extractOptionArgumentValue<T>(options, shortName, name);
    });

    return defaultArgumentValue;
}

template <>
inline bool OptionManager::defineOption(bool& referenceToMember,
                                        const char shortName,
                                        const CommandLineOption::Name_t& name,
                                        const CommandLineOptionSet::Description_t& description,
                                        const OptionType optionType,
                                        bool defaultArgumentValue)
{
    m_optionSet.addOption(CommandLineOptionSet::Entry{
        shortName,
        name,
        description,
        optionType,
        {cxx::TypeInfo<bool>::NAME},
        CommandLineOption::Argument_t(cxx::TruncateToCapacity, cxx::convert::toString(defaultArgumentValue))});

    m_assignments.emplace_back([this, &referenceToMember, optionType, shortName, name](CommandLineOption& options) {
        if (optionType == OptionType::SWITCH)
        {
            if (shortName != CommandLineOptionSet::NO_SHORT_OPTION)
            {
                referenceToMember = options.has(CommandLineOption::Name_t{cxx::TruncateToCapacity, &shortName, 1});
            }
            else
            {
                referenceToMember = options.has(name);
            }
        }
        else
        {
            referenceToMember = extractOptionArgumentValue<bool>(options, shortName, name);
        }
    });
    return defaultArgumentValue;
}
} // namespace internal
} // namespace posix
} // namespace iox

#endif
