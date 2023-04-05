// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
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

#include "iceoryx_platform/unistd.hpp"

int iox_close(int fd)
{
    return close(fd);
}

int iox_fchown(int fd, uid_t owner, gid_t group)
{
    return fchown(fd, owner, group);
}

int iox_access(const char* pathname, int mode)
{
    return access(pathname, mode);
}

int iox_unlink(const char* pathname)
{
    return unlink(pathname);
}

iox_off_t iox_lseek(int fd, iox_off_t offset, int whence)
{
    return lseek(fd, offset, whence);
}

iox_ssize_t iox_read(int fd, void* buf, size_t count)
{
    return read(fd, buf, count);
}
