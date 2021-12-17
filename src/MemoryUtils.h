#ifndef __ZHM5RANDOMIZER_SRC_MEMORYUTILS_H__
#define __ZHM5RANDOMIZER_SRC_MEMORYUTILS_H__

namespace hitman_randomizer {

class MemoryUtils {
 private:
  static void* trampoline_memory_base;

 public:
  static int DetourCall(void* hook_call_addr, const void* hook_function);
  static void DetourVFTCall(void** vft_entry_addr, void* hook_function,
                            void** original_fn_ptr);
};

}  // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_MEMORYUTILS_H__
