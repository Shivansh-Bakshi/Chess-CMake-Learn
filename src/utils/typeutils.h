#ifndef CH_TYPEUTILS_H
#define CH_TYPEUTILS_H

#include <iostream>

namespace ch {
    namespace utils {
        template <typename Enumeration>
        auto as_int8(Enumeration const value)
            -> typename std::underlying_type<Enumeration>::type
        {
            return static_cast<typename std::underlying_type<Enumeration>::type>(value);
        }
    }
}

#endif