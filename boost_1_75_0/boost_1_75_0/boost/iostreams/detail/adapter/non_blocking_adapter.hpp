// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/detail/ios.hpp>  // streamsize, seekdir, openmode.
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/write.hpp>

namespace boost { namespace iostreams {

template<typename Device>
class non_blocking_adapter {
public:
    typedef typename char_type_of<Device>::type char_type;
    struct category
        : mode_of<Device>::type, device_tag
        { };
    explicit non_blocking_adapter(Device& dev) : device_(dev) { }
    std::streamsize read(char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = iostreams::read(device_, s + result, n - result);
            if (amt == -1)
                break;
            result += amt;
        }
        return result != 0 ? result : -1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = 
                iostreams::write(device_, s + result, n - result);
            // write errors, like EOF on read, need to be handled.
            if (amt == -1)
                break;
            result += amt;
        }
        return result;    
    }
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which = 
                             BOOST_IOS::in | BOOST_IOS::out )
    { return iostreams::seek(device_, off, way, which); }
public:
    non_blocking_adapter& operator=(const non_blocking_adapter&);
    Device& device_;
};

} } // End namespace iostreams.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED

/* non_blocking_adapter.hpp
1+/2eI/sPUOEEuVu/GG4iGQirGnCI4JQ3Pub8UrvqFjG6bZguD5hi00kWtPaUEyLf7WZiwrAgMAz+CRhM+Sr0O4eblqP9/fnaS/hng80WdBaIAxSAdyoBz5DwGMtdU2qDJHmt7TdZjeVbihNWSo7pPg8QGAyRvsO++PDI23xzV3ajy8KjwHofHW3SUAzj24JD5JnX1jYHfySo1mN78K2keYAUDWZMb31gNCPjChIvu9CKBi68ngRvH32SPGVyBrm2gpw4GoB8Xy78mo5/9qyOH9EBdWBrNGZdJrQXtuy698PFqy6Aj03Pmn0z5HhAwcSB6/TfgyjtBhscOzcqTiO3+KsnAk0bWybBTaBBoTMH91gRLrj76H8p6vMc1yvKkYDkgAX65iolg0VVQFiy8Cd8x7xLTXPp5YvyYfo6JNuQ0SbvuWbkN5LGhYaZ1fxTP1lRYDXqeHRqNvua6DgiSgeaP8WMsvFOBfT3jv2qDtB6MFLoH0xd7a20/x68Nzs7dXFVoR4gMze7piB0ulU/Bvq+EYx4IwB0BaPbLCkD/Wqg9P8shHppTpKUXday4FDI9vqGfmMGulvAd+g4eThTcxGOpA7VfWlpTRmsut+KRIGvkU5oX/Fhgh7faJ0Fp+FWXQRic8GHPPTr00Gn4LLR0CbFyebmVtoBVW0N2f8NhrXc9JyieLbSwb1F2pNR4vFoEnbQ2GS5XmrFM7w+X33
*/