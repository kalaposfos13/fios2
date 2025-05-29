// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/scm_rev.h"

#define GIT_REV      "da9b26fa1e0a4b9e34dd9f08e7632676c7bfee9a"
#define GIT_BRANCH   "HEAD"
#define GIT_DESC     "v.0.2.0-0-gda9b26fa-dirty"

namespace Common {

const char g_scm_rev[]      = GIT_REV;
const char g_scm_branch[]   = GIT_BRANCH;
const char g_scm_desc[]     = GIT_DESC;

} // namespace

