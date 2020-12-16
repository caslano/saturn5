// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>                        // member template friends.
#include <boost/core/typeinfo.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>          // openmode.
#include <boost/iostreams/detail/streambuf.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // MSVC.

namespace boost { namespace iostreams { namespace detail {

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
class chain_base;

template<typename Chain, typename Access, typename Mode> class chainbuf;

#define BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base) \
    using base::eback; using base::gptr; using base::egptr; \
    using base::setg; using base::gbump; using base::pbase; \
    using base::pptr; using base::epptr; using base::setp; \
    using base::pbump; using base::underflow; using base::pbackfail; \
    using base::xsgetn; using base::overflow; using base::xsputn; \
    using base::sync; using base::seekoff; using base::seekpos; \
    /**/

template<typename Ch, typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch) >
class linked_streambuf : public BOOST_IOSTREAMS_BASIC_STREAMBUF(Ch, Tr) {
protected:
    linked_streambuf() : flags_(0) { }
    void set_true_eof(bool eof) 
    { 
        flags_ = (flags_ & ~f_true_eof) | (eof ? f_true_eof : 0); 
    }
public:

    // Should be called only after receiving an ordinary EOF indication,
    // to confirm that it represents EOF rather than WOULD_BLOCK.
    bool true_eof() const { return (flags_ & f_true_eof) != 0; }
protected:

    //----------grant friendship to chain_base and chainbuf-------------------//

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    template< typename Self, typename ChT, typename TrT,
              typename Alloc, typename Mode >
    friend class chain_base;
    template<typename Chain, typename Mode, typename Access>
    friend class chainbuf;
    template<typename U>
    friend class member_close_operation; 
#else
    public:
        typedef BOOST_IOSTREAMS_BASIC_STREAMBUF(Ch, Tr) base;
        BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base)
#endif
    void close(BOOST_IOS::openmode which)
    {
        if ( which == BOOST_IOS::in && 
            (flags_ & f_input_closed) == 0 )
        {
            flags_ |= f_input_closed;
            close_impl(which);
        }
        if ( which == BOOST_IOS::out && 
            (flags_ & f_output_closed) == 0 )
        {
            flags_ |= f_output_closed;
            close_impl(which);
        }
    }
    void set_needs_close()
    {
        flags_ &= ~(f_input_closed | f_output_closed);
    }
    virtual void set_next(linked_streambuf<Ch, Tr>* /* next */) { }
    virtual void close_impl(BOOST_IOS::openmode) = 0;
    virtual bool auto_close() const = 0;
    virtual void set_auto_close(bool) = 0;
    virtual bool strict_sync() = 0;
    virtual const boost::core::typeinfo& component_type() const = 0;
    virtual void* component_impl() = 0;
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    private:
#else
    public:
#endif
private:
    enum flag_type {
        f_true_eof       = 1,
        f_input_closed   = f_true_eof << 1,
        f_output_closed  = f_input_closed << 1
    };
    int flags_;
};

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED

/* linked_streambuf.hpp
T3PaPdSmNtreL4PlHaQz8rbYvm5qc9sXV60oL4miv5O/eX9n286xfYta/4r1cyvRtC/Ib9wXet68Ua3/FSUkmPYP+Y37R+VPhRvU+qPWbyyfaZ/p/Jnss46yz9ZisWcR++/fOf5+Rf0dvj/9hnm64LzQPO11XJVXtHXfqptcav8Ef4myb7edr/etzN/FZXgwed635HeNKynBPK7Qd+/LVbU1pnHlKlvvt9IK/jSNLa3fTmNJ2uG2t9Q3zWVvVS+XzU92spyh1la22Dw/zOYcM6MYT+R3jSdVgjlePgp750dpb/TD5rKfePDZ9NbXVZuitv0Usf2mLsENHpa2vSK23+eyfXVp1ery4tIVq4q9258yTPOZPgd8S63/Onmm0R7RpyYFVpkuR5a3OK89r9YfsH6AtmF/kd84r+lz2WfU+stM+07n7SR5uaOv8vWxy1Z+S1dL2mfd6vhWNT6S/IrYTNN2Jqj1C9kvpPkrQ6WvsFJZVslffXnnr9WZbfqDMQf++Jn+5ER//Of8yQmhvnMsRYl6f28P0T+C/jm2fsdC7RN8XHQGkk6SPrcHCZ2/PIX8rbu38+Rbp31y8+/ornre1exKhkCwPzbNAwXLqkpLm50/m/og+Zr7Sk/zcA7hPvd11m+LoX47sEV+wF2/itIrLEtvN+Bhu87t7O8Wvp1H2E590A7V48vbdhyqd4yFh5V+cc0a0zHIpdtdjTvCXSKd27ns/FiP1tvbWl96WC2nfo6+1F31Jeoh9pom9lqTEm6ve5lkGqYF7fW5gvOnT5+xcGFBzoyF0xfMzl80Oy+3oKJ2Zeg9sTvSVPs+Z7abKsfZPsZgS+3LaObLS9nUmbJddV7RPbzOO9FtbKnOq4tW1JZ6qzPluOe9EuO+dujq+aON7VP7To9vtufwVW5oR19ls09yZB/m2V3t5U+/uPjN+1f0O/rxbdtyXhv68HGuz7vZy+t/f8ng2wsf6LSh80Ff2gf3PdZ+vs27lW/z1GO/vnxvlzsfffz2hYN2TVr2YPv5Npt9mCP5PLefbzMzPMsTT/T+28q8sk+/1mnElypvXds1ko/xf58vdHv6PKvwCYkTXAPvR85x/H0c2Ry6ryVj4xjSDVkvefdw6ZEAn4A94F6YDp+EA+BT8Cz4DJwIfwzPgQfgVPgTOB02wBx4EM6FP4UXwRfgSvgzWA0btL+h3BOSe1bHXP6G35Xn//WwI3wQ9oUPwcFwNxwOH4GnSXqMwz9llr6Hgk2k/CQkW8q/0+G/MxDeDTPgPVL+1+EUlZby9L0B+rKhvFulvNukvC9LeV+T8rYo+5GW8rbp61au56W87kov+KuU9lfBVFgNs2Ct2PsKeBn8PCyCV8Er4TXwBvhFeDdcB78Jr4VPwA3weXg9/C3cBI/AL8E34I3wbZUWv5vQdZu095jL7+YP0u4/wkRIGdpe+ZLvXIO9XpV8r4m9fin2+o3Y63WYrdJN/iL7pLzDyDGXv8h7Yq8P4Ej4IZwJP4KF8O+wHJ6E18F/wq9A+4B3H4iDj4r+czCRdANMhodgB/iKpI/DkfocD12pT5xjTL4k7SOv1s8PRNa/X/QfcOjXt1D+m6L/lvZLUucKWn+Nyy+J8rVeYyt6IxO9+cO8/iHr/4Y/BbIfaUSsj/A1QNy+MovXNveXWUF6M+Lwm6Gz4geBhPxnFjfw3P6BeCt7ndmXppDl21gfyadmI+t3IAeRkH/NyXWsuzboZ5MBj7F8P2U097eBrAv53Ky5trnfzV2kdyOHkA+RSevRQ9z+OOvXN/fJ2UX6KNty+uZU0sZ6mLoh6KOTDQsRp6/OGtJbELfPzk6WbYIHoNN3Z3dd0H/n6IZwH54+14X78RQ=
*/