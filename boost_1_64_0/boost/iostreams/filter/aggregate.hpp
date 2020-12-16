// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_AGGREGATE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_AGGREGATE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                          // copy, min.
#include <boost/assert.hpp>
#include <iterator>                           // back_inserter
#include <vector>
#include <boost/iostreams/constants.hpp>      // default_device_buffer_size 
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>     // openmode, streamsize.
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/read.hpp>           // check_eof 
#include <boost/iostreams/write.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

//
// Template name: aggregate_filter.
// Template parameters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Utility for defining DualUseFilters which filter an
//      entire stream at once. To use, override the protected virtual
//      member do_filter.
// Note: This filter should not be copied while it is in use.
//
template<typename Ch, typename Alloc = std::allocator<Ch> >
class aggregate_filter  {
public:
    typedef Ch char_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    aggregate_filter() : ptr_(0), state_(0) { }
    virtual ~aggregate_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        BOOST_ASSERT(!(state_ & f_write));
        state_ |= f_read;
        if (!(state_ & f_eof))
            do_read(src);
        std::streamsize amt =
            (std::min)(n, static_cast<std::streamsize>(data_.size() - ptr_));
        if (amt) {
            BOOST_IOSTREAMS_CHAR_TRAITS(char_type)::copy(s, &data_[ptr_], amt);
            ptr_ += amt;
        }
        return detail::check_eof(amt);
    }

    template<typename Sink>
    std::streamsize write(Sink&, const char_type* s, std::streamsize n)
    {
        BOOST_ASSERT(!(state_ & f_read));
        state_ |= f_write;
        data_.insert(data_.end(), s, s + n);
        return n;
    }

    template<typename Sink>
    void close(Sink& sink, BOOST_IOS::openmode which)
    {
        if ((state_ & f_read) != 0 && which == BOOST_IOS::in)
            close_impl();
        if ((state_ & f_write) != 0 && which == BOOST_IOS::out) {
            try {
                vector_type filtered;
                do_filter(data_, filtered);
                do_write( 
                    sink, &filtered[0],
                    static_cast<std::streamsize>(filtered.size())
                );
            } catch (...) {
                close_impl();
                throw;
            }
            close_impl();
        }
    }

protected:
    typedef std::vector<Ch, Alloc>           vector_type;
    typedef typename vector_type::size_type  size_type;
private:
    virtual void do_filter(const vector_type& src, vector_type& dest) = 0;
    virtual void do_close() { }

    template<typename Source>
    void do_read(Source& src)
    {
        using std::streamsize;
        vector_type data;
        while (true) {
            const std::streamsize  size = default_device_buffer_size;
            Ch                     buf[size];
            std::streamsize        amt;
            if ((amt = boost::iostreams::read(src, buf, size)) == -1)
                break;
            data.insert(data.end(), buf, buf + amt);
        }
        do_filter(data, data_);
        state_ |= f_eof;
    }

    template<typename Sink>
    void do_write(Sink& sink, const char_type* s, std::streamsize n) 
    { 
        typedef typename iostreams::category_of<Sink>::type  category;
        typedef is_convertible<category, output>             can_write;
        do_write(sink, s, n, can_write()); 
    }

    template<typename Sink>
    void do_write(Sink& sink, const char_type* s, std::streamsize n, mpl::true_) 
    { iostreams::write(sink, s, n); }

    template<typename Sink>
    void do_write(Sink&, const char_type*, std::streamsize, mpl::false_) { }

    void close_impl()
    {
        data_.clear();
        ptr_ = 0;
        state_ = 0;
        do_close();
    }

    enum flag_type {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1
    };

    // Note: typically will not be copied while vector contains data.
    vector_type  data_;
    size_type    ptr_;
    int          state_;
};
BOOST_IOSTREAMS_PIPABLE(aggregate_filter, 1)

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_AGGREGATE_FILTER_HPP_INCLUDED

/* aggregate.hpp
sPjhLXL4vRVOhl+GOfAr8Ivwa/BaeDtElF/kLng3fBJ+HT4PvyHt+gC+DLfDP8FvwWPwXtiRbe+Eg+AuOBo+CM+B34W58BFYAh+Fa+Bj8Gb4BKyHe+F++AP4M7gPHoFPwTfgfpgUxz0O6Ic/ht3gATgcPgcnw4MwAH8KZ8MG+Fl4CNbBl+EWeBjeAV+F9fCXcD/8NXwdNsKT8AjsEx+sZxZ8A86Cf4ZL4NuwEr4D6+C7cLMs3waPw53wBPwu/At8DH4g+zOg72Oo61u1PxPhBOm356FncwYcAi+AQyV9mp3W5SAtlDNbylkk5Vwk5ZCmHNKOcipbKGe8lHOOlJMt5ZCmHNLa31iuz+DpUo7T33iElDMK9oSZsLekB8HRcDgcI+WeDjMlfRzW6esSrrukfOf3MXqIv2VP2B/2glkwDWbD3jLO+8AlMB2uhH3hlbAfVN97gFvgALgdDoQPwEEh/0J9naDsxFwV2Z+ywaNeo0HP5E95zKOelenNTzKlFb3+/+V+kh8qX0nj9w7wlfzP+UniI4mv5P+fn+T/go8k/pH4ScZ8JGM+ktH5SPb/HTZASpCNyC7kEHICSf19ojUJWYKsR3YhB34f84OM/WK/2C/2i/1iv9gv9ov9Yr/Y71/snQ18VlUZwO+777EX2Ma+GDAmAiICDkQEBB1fCoQ4BBRFHWMbX7KP2GaYULPEDKmWUSJZkVmZWU3DJLVcil+pNRUVDRNLixRzoilmZv973uc9O7vvebf7Dvrey+/w3733Oeee85yPe+65z31uz6/n9x9g/7929fKjZf+fmO9of7hLAtq3nfplEuawUNs0oN02a8ascxbh+7yiodYxbFfW257NEq+jr/IkznVeP6dLv4JixyN2I+s7+OydyAF+6lneMHcbXkoemwd4bBEx0MGhlNfXrbbn/ZWSHxo4x+lrybukx78c4t+SoZ4r19U1VK5z/VA6Ys+8C3vmF5RcYSBs3/+I2u5vff5Mmtp2510jTfzla5vsp5RMQWCek26139H50mmEXFrOb6haTpVqO+LnkEMqMJM9Nh+epOO1t1JyOylTu+129eoKwx7sLypOMaU7Run1otyO3wG4R+JSb/zKdVxX7GUVNxiYjL102O4/OZ/ykvBF4k/2VfHP9xht5CX+nsaxzQSX10q7mWezfbV8EyATO9hLBqo18IrVKzGFFdvYjIEe21iP79h8ebZPnbOvQ51r+6V35ZjUnYqTHt7vqQ/astJpg/hU5JxKT+hOf3/AbN9ZSfKMU+zPziNc5tqeDvK07/qaUhTsbd/ahuxcJV9ibdukpdthZagNNSxfU1lOdN1+ViiZ43m2Emdpy5Y0RB8csrZbkVf5HaFKuroatep2X6eOj0e2j+4fjujStI/fqORGkKt0p/2bE66713af9tuUTKpjfvvjp+nkm/Z2J3yRtpSa79+mzWgf2jcxZWaf6E23DdmvdSE2OlK3N4sz2cWEJMIiwnjXts2oW4at8qoOY2uZtuv7pZKbY6tT0vDaEy7XbeEBdexsaz1KPO/7GlqX73OcVGWb+i5gm7ed3HcD8ijEEsr0G2VXG0hLTIqLT0+b6f6PY+v0hEz0H08a4+jT2zNU8J5Hjy1PqfMUcKbIc5nfbPhERmS9pXR6/Sjz2CEu72C3vV8iT5M6KZY6KSroUCehClVVY6+byUr+ZFvdkFb0ujlZHTvVWjcSL6rOZhRE6qxadGbRfWd6m+tXbxPCbVk6yyVxoX6zBl7uzhUMvdWWrcOIu2HdWrHlYpDkmNq2zxeM8v4ty5WtXVVDp8sXHe9Qx8+Le5OnxD8PpDh7AwkWvVnTqa1ZV6/b9FZ1fKy2Lx5cqK7Z2m73frU=
*/