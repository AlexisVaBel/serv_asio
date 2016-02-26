#include "mime_type.hpp"

namespace http {
namespace mime_types{
struct mapping{
    const char* extension;
    const char* mime_type;
}mappings[]={
{"htm","text/html"},
{"html","text/html"},
{"gif","image/gif"},
{"jpg","image/jpeg"},
{"png","image/png"}
};


std::string extension_to_type(const std::string &extension){
    for(mapping m:mappings){
        if(m.extension==extension){
            return m.mime_type;
        }
    }
    return "text/plain";
}

}
}

