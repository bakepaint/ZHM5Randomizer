#ifndef __ZHM5RANDOMIZER_SRC_PROCESS_H__
#define __ZHM5RANDOMIZER_SRC_PROCESS_H__

#include <string>

namespace Process {

// Get filename of exe file the current process was started from.
std::wstring getModuleFilename(int moduleHandle = 0);

} // namespace Process

#endif // __ZHM5RANDOMIZER_SRC_PROCESS_H__
