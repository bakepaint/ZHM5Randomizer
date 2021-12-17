#ifndef __ZHM5RANDOMIZER_SRC_CLIENTVALIDATION_H__
#define __ZHM5RANDOMIZER_SRC_CLIENTVALIDATION_H__

namespace Validation {

enum class Status {
    Ok,
    NotTrusted,
    InvalidSubjectName,
    UnkownError,
};

// Checks if the current client executable has a valid digital signature with IOI as the
// subject. Return of Status::Ok indicates a successful signature validation.
Status isValidClient();

} // namespace Validation

#endif // __ZHM5RANDOMIZER_SRC_CLIENTVALIDATION_H__
