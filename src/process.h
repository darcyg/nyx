/* Copyright 2014-2016 Gregor Uhlenheuer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NYX_PROCESS_H__
#define __NYX_PROCESS_H__

#include "nyx.h"

pid_t
determine_pid(const char *name, nyx_t *nyx);

int
write_pid(pid_t pid, const char *name, nyx_t *nyx);

int
check_process_running(pid_t pid);

int
clear_pid(const char *name, nyx_t *nyx);

#endif

/* vim: set et sw=4 sts=4 tw=80: */
