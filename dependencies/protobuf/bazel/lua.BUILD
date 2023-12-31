# Copyright (c) 2009-2021, Google LLC
# All rights reserved.
#
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file or at
# https://developers.google.com/open-source/licenses/bsd

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "liblua_headers",
    hdrs = [
        "src/lauxlib.h",
        "src/lua.h",
        "src/lua.hpp",
        "src/luaconf.h",
        "src/lualib.h",
    ],
    defines = ["LUA_USE_LINUX"],
    includes = ["src"],
)

cc_library(
    name = "liblua",
    srcs = [
        "src/lapi.c",
        "src/lapi.h",
        "src/lauxlib.c",
        "src/lauxlib.h",
        "src/lbaselib.c",
        "src/lbitlib.c",
        "src/lcode.c",
        "src/lcode.h",
        "src/lcorolib.c",
        "src/lctype.c",
        "src/lctype.h",
        "src/ldblib.c",
        "src/ldebug.c",
        "src/ldebug.h",
        "src/ldo.c",
        "src/ldo.h",
        "src/ldump.c",
        "src/lfunc.c",
        "src/lfunc.h",
        "src/lgc.c",
        "src/lgc.h",
        "src/linit.c",
        "src/liolib.c",
        "src/llex.c",
        "src/llex.h",
        "src/llimits.h",
        "src/lmathlib.c",
        "src/lmem.c",
        "src/lmem.h",
        "src/loadlib.c",
        "src/lobject.c",
        "src/lobject.h",
        "src/lopcodes.c",
        "src/lopcodes.h",
        "src/loslib.c",
        "src/lparser.c",
        "src/lparser.h",
        "src/lstate.c",
        "src/lstate.h",
        "src/lstring.c",
        "src/lstring.h",
        "src/lstrlib.c",
        "src/ltable.c",
        "src/ltable.h",
        "src/ltablib.c",
        "src/ltm.c",
        "src/ltm.h",
        "src/lundump.c",
        "src/lundump.h",
        "src/lvm.c",
        "src/lvm.h",
        "src/lzio.c",
        "src/lzio.h",
    ],
    hdrs = [
        "src/lauxlib.h",
        "src/lua.h",
        "src/lua.hpp",
        "src/luaconf.h",
        "src/lualib.h",
    ],
    defines = ["LUA_USE_LINUX"],
    includes = ["src"],
    linkopts = [
        "-lm",
        "-ldl",
    ],
)

cc_binary(
    name = "lua",
    srcs = [
        "src/lua.c",
    ],
    linkopts = [
        "-lreadline",
        "-rdynamic",
    ],
    deps = [
        ":liblua",
    ],
)
