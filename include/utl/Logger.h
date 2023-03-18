/////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, The Regents of the University of California
// All rights reserved.
//
// BSD 3-Clause License
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>


namespace utl {


// Keep this sorted
#define FOREACH_TOOL(X) \
  X(ANT)                \
  X(CTS)                \
  X(DFT)                \
  X(DPL)                \
  X(DPO)                \
  X(DRT)                \
  X(DST)                \
  X(FIN)                \
  X(FLW)                \
  X(GPL)                \
  X(GRT)                \
  X(GUI)                \
  X(IFP)                \
  X(MPL)                \
  X(ODB)                \
  X(ORD)                \
  X(PAD)                \
  X(PAR)                \
  X(PDN)                \
  X(PDR)                \
  X(PPL)                \
  X(PSM)                \
  X(PSN)                \
  X(RCX)                \
  X(RMP)                \
  X(RSZ)                \
  X(STA)                \
  X(STT)                \
  X(TAP)                \
  X(UKN)                \
  X(UPF)                \
  X(UTL)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

// backward compatibility with fmt versions older than 8
#if FMT_VERSION >= 80000
#define FMT_RUNTIME(format_string) fmt::runtime(format_string)
#else
#define FMT_RUNTIME(format_string) format_string
#endif

enum ToolId
{
  FOREACH_TOOL(GENERATE_ENUM)
      SIZE  // the number of tools, do not put anything after this
};

class Logger
{
 public:
  // Use nullptr if messages or metrics are not logged to a file.
  Logger(void *){}
  Logger(){}
  ~Logger(){}
  template <typename... Args>
  inline void report(const std::string& message, const Args&... args)
  {
  }

  // Do NOT call this directly, use the debugPrint macro  instead (defined
  // below)
  template <typename... Args>
  inline void debug(ToolId tool,
                    const std::string& group,
                    const std::string& message,
                    const Args&... args)
  {
  }

  template <typename... Args>
  inline void info(ToolId tool,
                   int id,
                   const std::string& message,
                   const Args&... args)
  {
  }

  template <typename... Args>
  inline void warn(ToolId tool,
                   int id,
                   const std::string& message,
                   const Args&... args)
  {
  }

  template <typename... Args>
  __attribute__((noreturn)) inline void error(ToolId tool,
                                              int id,
                                              const std::string& message,
                                              const Args&... args)
  {
    std::runtime_error except(0);
    // Exception should be caught by swig error handler.
    throw except;
  }

  template <typename... Args>
  __attribute__((noreturn)) void critical(ToolId tool,
                                          int id,
                                          const std::string& message,
                                          const Args&... args)
  {
    exit(EXIT_FAILURE);
  }


 private:

};

// Use this macro for any debug messages.  It avoids evaluating message and
// varargs when no message is issued.
#define debugPrint(logger, tool, group, level, ...) {}


}  // namespace utl
