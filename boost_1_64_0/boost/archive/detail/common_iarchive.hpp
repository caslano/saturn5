#ifndef BOOST_ARCHIVE_DETAIL_COMMON_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_COMMON_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// common_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/archive/detail/basic_pointer_iserializer.hpp>
#include <boost/archive/detail/interface_iarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

class extended_type_info;

// note: referred to as Curiously Recurring Template Patter (CRTP)
template<class Archive>
class BOOST_SYMBOL_VISIBLE common_iarchive :
    public basic_iarchive,
    public interface_iarchive<Archive>
{
    friend class interface_iarchive<Archive>;
    friend class basic_iarchive;
private:
    virtual void vload(version_type & t){
        * this->This() >> t;
    }
    virtual void vload(object_id_type & t){
        * this->This() >> t;
    }
    virtual void vload(class_id_type & t){
        * this->This() >> t;
    }
    virtual void vload(class_id_optional_type & t){
        * this->This() >> t;
    }
    virtual void vload(tracking_type & t){
        * this->This() >> t;
    }
    virtual void vload(class_name_type &s){
        * this->This() >> s;
    }
protected:
    // default processing - invoke serialization library
    template<class T>
    void load_override(T & t){
        archive::load(* this->This(), t);
    }
    // default implementations of functions which emit start/end tags for
    // archive types that require them.
    void load_start(const char * /*name*/){}
    void load_end(const char * /*name*/){}
    // default archive initialization
    common_iarchive(unsigned int flags = 0) :
        basic_iarchive(flags),
        interface_iarchive<Archive>()
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_DETAIL_COMMON_IARCHIVE_HPP


/* common_iarchive.hpp
YhGxglhJrCNeJl4n3iK2E/uJL4nDxBEihcQkcUh8khXJjeRB8iJ5k3xJc0lBpAhSNGkVaStpOymblEMqI1WSakn1pMukRtJ1Uiupg9RD6iW9JBHIDDKLzCXzyHyygGxGdiA7kb3JPmQ/cgA5kBxGjiInkbPIOeRD5CJyFbmaXEtuILeS28gd5EfkPvIgeYhMoJAobAqPoksRUkQUC4oLZRrFk+JF8aX4UQIp4ZQoSjwlmbKZkkrJouRRCihFlPOUW5ROSg+ljzJIeUkZoTCpHCqXKqbaUKXUadS51CBqMDWUGkmNpa6hJlATqcnUrdQ0agY1k5pDLaAWUsuoVdQaaiP1FrWL2k3tpfZTB6g4mjyNRVOn8WgCmhHNgeZO86bNpQXQQmiRtDW0zbTttDRaJi2LVk6roNXSGmiNtDZaB+0RbZA2TCPJ0GTkZXRlRDJiGScZf5lAmSCZCJlomXiZJJnNMrtk0mWyZUplymQqZCplzst0ynTJ9Mj0y7yUGZbB0HF0Bp1J59C5dCHdiC6lO9C96L70MPoqeiI9mZ5C30rfTs+jF9LL6VX08/R6+mX6dXozvZXeRe+mD9BH6KN0iqyyLFuWK8uXFclayEpkPWTnyvrJBsiGy0bJxsquk02RTZVNl82SLZEtl62QrZVtkm2WbZXtle2THZIlMWgMOkOZocsQMMQMF4Y7w5PhxfBh+DH8GaGMcEYCI52Ry8hj5DOKGKWMMkYlo4lxnXGL8YjRxxhmjDBwcgw5jhxXTldOKGcjJ5VzkPOWC5OLllslt0YuWS5Fbpdcmly2XJ7cIbliuRK5SrkauXq5brl+uQG5ETmCPE2eJc+XN5K3kXeTd5f3kw+UD5YPk4+UT5RPkt8unyWfK39IPl++UL5Wvk6+Sb5Fvlu+T35QfliersBW4CjwFAQKQgWxgpWCk4K7go9CoEKUQrTCKoV1CqkKGQrFCqUKZQoVCtUKNQqXFZoU2hVGFEhMOlOVyWcaMa2YLkw35jSmF3MuM4AZygxjRjDXMBOZKcytzF3MNGY2M4dZzKxk1jKbmbeY7cweZi9zgDnEHGWqK3IVRYpmihJFN0VPRT/FcMVIxSjFWMXtipmKOYq5iiWK5YpVig2KzYqdit2KBBaNJc9SZnFYuiwBS8iyYklZTiwX1jRWICuEFcoKZ61jJbCSWKmsXawMVharjFXJqmHVsS6zWlgvWSQlihJDianEUlJVUlfSVTJTslGSKrkpeSn5KoUpRShFKsUqpSllKOUoFSgVK5UpVSnVKjUqXVe6pdSq1KHUpdSj1Kv0UmlIiaLMUOYp85XNlJ2UA5SDleOV1yhvV05XzlLOUT6kXKpcoVytXK/coNys3KH8SHlAeVB5VJmkwlRhq1ioWKlIVFxUpql4qviqhKpEqcSrrFNJUElWSVXJUslWyVcpUilVqVCpUTmv0qTSonJLpV2lS6VHZVBlRIWlqq4qVjVTdVOdpuqt6q+6SjVRNU01QzVTNU+1QLVQtUS1TPW8aqNqq2qv6ogqTo2gJq+mrMZV46kZqYnULNQc1DzVvNXC1MLV1qitU0tR26yWppavVqhWpFaiVqFWr9ao1qzWotapNqA2rDaqRlDnqeuqi9TF6lbqEnUndXd1L3VfdT/1EPVw9Wj1BPUk9V3q2er56tXqdepN6i3qt9T71F+qUzSYGqoafA2hhpGGmYZUw03DQ8NLw1cjWiNRY6vGdo1MjTyNQxplGuUa9RodGgMaQxoUtjqby+axLdg2bAe2E9uD7cMOYAezw9hR7Fj2GvY6dgp7MzudncnOYR9i57NL2eXsOnYLu5XdwR5kD7ExmiRNmiZTU1lTV1OoKdKUak7T9NQ=
*/