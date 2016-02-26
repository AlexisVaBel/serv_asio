#ifndef MIME_TYPE_H
#define MIME_TYPE_H
#include <string>

namespace http{
namespace mime_types{
    std::string extension_to_type(const std::string &extension);
}
}


#endif // MIME_TYPE_H
