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
gbgSYE4w43B0Hv42Nu5ZQ45OTz1QGqCMLRzWJW5nir71/aI70qpBpb7S1BPRfLe4cFMHqKAW8sbHhYU1aSacTp2o7hMjkR+/oAd3FSCJpY+UUeybJPDlDHQvePxGaH/ac2FP1urvvFnw6Cuct3zkjK1hQFMqYX1BdcbIxwfldfpyoqPYTRne9dYfZkYZHshlUMowyO0absKVeavtF/hOzitkqAOVpT4G3qqIhndt9NhuXRUzgkTWha0m7gZ4wjRRL1bOtlV5SRl1J4KS+FwSi05LHK1Pq2kZjlddrq3qLr1nsmQzx+N3c0usUOMpbrXn6GT1MUVBHjGYq8/a2JVyDpWNye5MDFsdsOursVgE1ahpaHr4q3o0ySqHPbbZXcfZfmolbYZWBQPrdz8/wDep9Q8l4cIbNSoH97Qugxi2XScaJmoqmpdGYVesK0KvAKbpJy1vhEmgqlN5lGbflQc5/+2+dty/dlw3f4ROY2c1tLaeYrPrMk2v2TNn1D53UAR/XogAEFotcQ5x93BR6AtION903eWbgi7jJh51mKmwNfeuosaY4NZnJ+tsOtxrMwEcYzjWHRchlyJsbj6JtdCApvUkmg8OWf3/JZoM88fkayknvvPF8zz63V6/Xci4P/ao5Mt9upkX82xjA0WAAiIjnMRqxoKXguk4o/GgC+ueRLIpXtbPSYouam5KBkk51BXo4WBHNCR2dNZBZA5PaMWUYbtDT0KnRimxtD7gSlBG0Au3QZAwYWET8L8DCoNP/c03wOOcwebt/37/WucYPYIbv6gza97lxgZEM9pNH5vvWinfvUy/Elb4XXh2LGdk8gfcjrez3/cbyOZ1Naxd+1QjWGoy9IiA5JhNBvkGvV2rM8j+JFfPQDjdfGOOCGvutKqzjvbTYPKguVi50hCNlAKJj9jqF0yF8ceHP9rEd1Dke2gw2Wt88wdR/S57pbblr15sX3BwPeeRxHHOyXG53R4ANOBfPEiGsEV0RmXyewMSccT/7SieKLemkZojCfe8B0BJnVWy+LV+rMlwiZplE3hLcxxqlf2QHFAHlVgvpjCrDsnrZmXAGGSWFjZqYHF+z8mbplHOJn96d2CiM9x2rllx06CxsTVORi79715vGXG7ZmnfnhncM2Ng69jNE9dNAVfnEA222wpCpUeRNasSAXl12JNQTybVh+ze55DGAxLVuVet139Z3skOoLPlGLmS07vYduwJBDLmqVrOFt0khjzzr+flmmIJpsWTKVwlez163fzqvo69PXnrVS04bY2r02Rk+/mWt8AJDXOB5HoXNyHVVA4jTPRPqc8B5xIpoj2q4bqlR2bIYZ6x0SRcTjeeoMFxrWjRpI5PuX1Xn41BnePCIi0xeOwK5X5emP4kBwzr9v0zS8NaZr3vrmzCBDHJWxk0VrDma/lTIfZ7+iHDkZj8ZmiSaMLyPgcFN4k1DueTLyjCedrHctsBggVIxeNDJ8TOViWndR1SSU/JO89xOSI3nR4dW4pRZ4K+aoYwqSjXO8gE3I0ytf3gIwvG5X5ud2vqNkt9AsMAtpGrqF008+Qifgxq4AZ61M8EY0w22OOKNlf3T+8NZL+wU/pqmeEuJLs5JnG2wenn+Z3BlTth60eonzjMhvQIAD07quNwvSjcW6rxNYJ6JoRzXF0bDxEu3k1dkkC4U8XciMe1IS+X0SvLjwQYSeep/+B/JNaIW9diJ1N1LDhf/rDr5W8M+zk4MfZju59WYruirtj0GaKtzJzY10JdWTgyCCSoM1OMiZdsToQ8QBNR7c+FlkN2P2x67cTEBGUQESC2RdZFZoYrppnZweWHjzkgb+mQRd/FGaKX5Y0R9WdP57vtP+ltNgVnr6w1B1W5E+Iccxjb0QEBSMu5I7A7LDeziCRLcz6NrrQHOd5mq54sdowywgGoiNvcteUetoEbyMFRDtScBI5idQWH2Dtmh0HtaI3gk/G0WA7esuz1RjQGB+fu/thf3biferQfNu/PDKbwQ2yHqq9PPiczK+Uo1mz3jGtmvEQmbDL/xchf68ZFM7ZITqqUT5ZWvAsDmYX6cDy0eF8fcKE8P0rRFK1HYEwIo+9mblv1WMzaD1oqqBhakwd4or3at87gEWIb7S7LX0z9ZST5Z2rS1qlYWahS9ot/5KDXo7Vf7pw7YVy33Ix1Q1mTQW6O05n6qfBxzrRV4+IeKqR5CGOaKJJaunU3TG59Z8iIqWI+m+GXgRQpBs4DTlhnJINezYH6jmFG5vHu/bgfxzdaTDKjChLNpdyhE8yoqm4twZD8rgmkYaVszh/pdEe6+VxGhbwk7u+uAumFi29XIOsytR2AjWlGOEbUfg2X1SGBU9d9PRa7k/F+ePB6QsKgX3f06xoyd0ONRNVSBhBWRzefvXLcC64bhUYA7GVhLnk8vtV/le4hR7Pq5rDxePmDWEp4rivcPIuxkdky21TPD6AL+fYupra9M0gBN/cnu3K+HbuBjVmWrpD7nm1fyye43ZD8OAvaPVGfiFuLRPzYgKzFr5ALqShYd1Oc+Tj0vFcrxjSN5LVe6pxxq4zjkZsyU8mxlKqKHdh2yBYs6bvIrlurZe+MnMOag9Xa6r+bholUXnI6VFbUgWm+7+IhxV8TYkNT+ntSL/LPTWLtJhXybCTpOOklTv+9ApOpXnCRVv7yy40NiIjI/qa5W0Sb+vW9cx/yLl5QQQqDc0uxsgKY35pc+d7pgNPS8/d5EzBEiCw9L/XzySzOr454Z/aQq+WmRD2se8bmXJN2GxBBcu4+4ytw7/14QeZS7TR9lOhWnDMciTZ97BiUCFIopMR0/urpQp6KADsGAENDBrg59aUgRSUg2Y1pSFZqi0E42II68j+ekvqUWM5zsm4zI/90plGV8hvkY5fqWysqtMu9V1hIdF3MMDUQU9fm4GthvlwqNW5uqc0w5fQTOndGfk4MySCB07sjtAMdtBfiKRA1j6kNK6aIN0Ad98XET1+Z58oVYE++7VFjmcONccBcU69jZJ5+cUzJVnncfIXWrt1ZMFzI1Kcin1K78GRgY4IbS19jJ7kP0BrrJO96h/YZQBRtayC/7JqvgAPbEgs48Q8y41slJfKqiAOPGnbwoql7bNNQYxmbUbkRRbn8dv7GlfcnYZY4JRrYEgVHGcgdCSH37EIubWrEcDk6JFyk+1u3f99PLe6OHvMj0Gl46pJ9dauevmSSiX8sRsa+TwjWqnmvjni6r8xJptfVqV+5I1LOcK5kOpCSYOKHSNK0SKACtvpRFb3fgymvO7B3c+USjRmDIQlbi1NbtCl9uZ+QmCaTJQ9nbvjJAwmcGM8b2Zw7vu+X8V3x7Wrjl8R+M/E6880R+SPlUJ/A8meXPJs17QUohM1+B3x3MH2J3NEeyDxf7dlN34/2gaeufZ+5Kx1Nww6ZkC6mG+Y9SRsQ7iHAaixk8I8QRRQjpV5NnJzfiQtsqYVvW0H8oTUwSTP7gIRV5GwOoUK09wPFMZCM9ipogtL0MWWh2DKAws10Gp8BC2p3r6FJin+J3OGHv7FPCZXBvBow/WpS2+EzQuVrojA7zriR+Of8sIeTYJSm7Y6i9Q6r6jX5YpZcQ5Lbl3r+WXES/S7Bk9JDBqI3OkupPhFyemMxbG38y2Jr7cvO+SEWLHGJR3troJCo8SRy2yjxV72jJfgJkQgwtM4cyGxTTMJYfp//EoZxSZWcV40G4G1QPUi919Apw+nR7mSMJl3NSbPEdt2qZ4JDbHWWz7AvbH/H8tyADbQLGmuG5nf8qQlg8JXiMs6UCb32W6jv13sEQH/rusqYMGdZ+S+OJfusdIh+T+7Ckk8wbscrDeYZp2O7IB9dRA/ue9QzomQlk9uiynksmhnTnKoYh6YCzVkrrWq/fa6dESfLhWZPCflqWANpdP1mnfC8XKvi5xK/7Vet4FntPaJv3k1Qt7FqNFvb3VfIr/GmAhMNcRIJ+nLWZhOv5vBQKJMtzKQ7oz73AvyPOEHGW7tTzZu0G2Wyqknof5Dppz3QAMp2voz/FoQjwe7vClxyjvsLDUUC/cUkB2/nZYB7YzaJYjN6UGUaTB/3XcSEMN+c/kkhvx0oUk4Vwlzs4wqsVaIDje1XEg72NX9/U5gU9wzmMxrEyZjyTjQcJNM437PfilfL3fMZP79/7gePy414rieeWKgRttC8sAZeVtz+WD48O2/fec6EcaZ1GB+WxmPBc99vZDOQM0WX7bBZoMiBDA8401Udztn1JbeaAiDcUodfn8eAd/P2LUXrjDlb88LyewvD2jeV9n7XDbDwlAfSA/1frW3glivJ3Yn7GaPij18H9QAqsmWiBpJjgCIOb6Y4No27KgOehDrHm3ntu4KYe1Nf8x1ItZDyGabXi1xqVK4JmHnZAV0rMDNX9JVzn0jMgJ7Jh5QVnkYie6nkjh8TGWdDdVvxJSXNNlID8aVRDfGK7LLP6/oECji30lFeHrhzUiWfdHVxoz4+6l2J1FQEutR5ipuS+Jl+3ejAy+HkA5T8CyCpJZwo61eDw/CLAELyrhObW6f72ZHreLML+O93XG6ZDdUCtaMlKyQwVQ9bWuwspN5xkuo0XaH4BASRVDd3KcV74tPUj6rPBbqqmmdUs2Ku1hQi+FXAhFfEhVGb1VmOSMOuEnfdO8VEWbKNj61hneMh3EWcd8FbE100oYFNCxbIVS7VzpKOt9zSYuTJMkvQitRuFvMwfJ7r4/VV3qgCxyTca/OacD3BTjgOtGAXx48PjzOv2EjyHIgNGkqx6xo9lcR0PrNjGRx5zaTpDIJ2pGZ2lPwXbGz3f+oj6xa++J5lZyrKt8x8j2dLdqSrAcsROiaDNki6rVQj1B2BCy1P8KyvhpJ7mENSZFSfdTgF6c6EgVtrx9tdjtFSV7iudntnbUgF2Uc3gKeHwA1UxhoInObXH55z5LZ7L47PqaL3d2z+lDj+vbiTeTpjIVvvd/yjna6436g6MFSuL82Hd+WwuMnN8BC5MUVl/UOmSFcPZWTM5BnGWexmrnj3u6FHRyKB2m/T+rwg4rO/Z5RTnQs4WfVnJZBuKbdH+4PD4SBqg3PJtMmQUV9FqsVjYo/F92ErOIIu+6t7j0m5i8jkqxto+tbbsUa7xI3iTczfVhrVqr//XftONG1HgdoLeKG3NJ8qd3IEP/Ef+gdBjAQwKVVb3AJc/pIfPBeGffoujs6Q+LgBk/y7JUMfnj5/56fTyNvaD/QjDH1/236uvfxLj/taXG+7HFw2d7b8HzaaMctx/9+Yk3DuPiX+zkPqdPYY8ro/QOml8jVzgE9rjQdOp6J5YVHbFPcarkCOD6ugSiJed5xNy5NNtVOiw+sb1JwzzQi1aQ70JLB2hrs+KRJEmxg1DADcrG4nS+1vm0m/jKwyfmKr1ZZkQZAPrKf7/O84M6cY/5r1hf4uQnMk8e6PnMm/G8J7E9GnRgu8/e4/4l5vbSu6TuLH900hguKA05IvCnO6TRs5xCn4vFTXF0smb5XLz6H/5Btip/vNCpi9Qf23FL+4sKORYX9VIP0xcnJNUN5TUx6//ot7a9Kg+632y/z5GKRh3zJufMxE5x6O83CyvvmAePfibX6/XK3NlyJ7WDmb/Pm/JuOa+7ORp/QXb+V4+/JW+G3jfn76/cuOnD+T6qc/gLjd9vfXXPrR9l+qev7+02gSfF7u0NpklGOGAjgV5byS6fFiNkHXpB6qLQSpjhndgmwGMO4hQBVKKVGo8BknheYxxm2IsZK1Uxu42z+kwc5eJv4ZpjpDmgJ0rNmk1TdPueeRIez/WrlaUP/W4ANoN90SzKIhGMyrsx2v7ps+C/0Z/e+JG1k6q8yCNV/8DyfkAn66r49J5w3PduSUXmbONDkO63czenmsa23Z8Vf2pcqcjczdMG03Dp5DaRDvs40UDdYIjX+loX0Q/s4zaWvucso2g0k2pXZGpam0FtXnoeR97c22OoGzWBUd89cD4hegp7fToHKSL5HqCdZAcNCZmWCynpwA2Kl3PJrcmDub1AqkpSoIb2FNg8bG3Xq9VnPb1kCVmVHvrCxiUl3MgeU5tlxddoAZV3JSB0RE08bFE7yYFV9yTSBquda2HplVSE3mCVPSEky5sKXmzDbMYM2yqDBBY9G7pwyOdtGfBt/wIipOPoZ7IJoTRnhk9ZAnim/ewMRmJ1AQRpuc87MLy+ps4M/zoOogZgNFs0DFNPRITSQwuNqcp3WnMyMegZrBdgVSd2XDw/Dfauoa6bavhOPiuGfswMSrNF0j6eNbktTcbqCtt7JSJrf1vPOui9rcBmKgP81H2AvTVcejPcTogUIEC6DzEpk5za3qF6+OVZWiy7ZfAAAs/9M7a7zyhRFKn9oMb60aFanEMLHfY+gqLiiThng/RaduilkNd7EK6uqHNOz2L93TMHnSdUWUJSTnzBw7Z/+qekLBNbaP51s63HvXh2x+tn5rdTPq+3awHtV60NpsVNxFAWNNJy7JEwN9uWo8f9j8XBSI/SBHX8cbqtodi9xeLlObwZUpJEJJlS31dPjQ+z7eG6Wjo89E4qU0q6vZIB4/+6YKaIZFnm7r5UD+VihkHzQDr921x3f9GxJZCSUgqYJW1xq1qZeZym85V1nebWZMPpSq2xP2SpR/AI34iPG7L//YHNjoGAXHPiZyOqdOFUEvCv64XQz/UOXrrzPOokFrSoTqAetCvqZi0om7pfuGK3MBC5KBWUgdyKvcQv0caWl0mrYDzkNoqErs6j8C8zsfxZ9PPzTSkcPomjioegXXxZWFhPYEUBJqTNPpxj1qzBjVoWA5WYDiSVw1g67haq271SkzO+FmokUZ2ETlHMURbPEvlu21uPVgmYgkddsgIxWKAkxT59/PIeSAjixfZnGz1/rUQGQ3nmllxWj9LT/uBQBWsxbDcEMDHTudDYsj9MUzI1bWzCiTE8s1ufjTkMAt/+0JlyOKwVNZlVFEQ0ModZ7E6u33KonkveYLkWRKTEhZvlGck1LinRnJJb0p/hVQCpWQgeKMzKDUQjuaD2uoKXDdUIBhdBWV+eVTjCyXOIZv8FsIa9Ne3KuLO0CdpBKzcel7TvLl7w09mb+5/VH8Biy+2F+krF/D59ADK0chE3GqkthSvoVXqd6Qg08OaMDrINJoVC6CTutdL8/tk+rP73JMMU9b/HzrkIbW8sotaNfUtGUVyhFGG7/Y/Gf6GvIv1Niim06IChCdNZLbt1BMeed71bTYF16JmR9PmtuyvNf1f1/EOs6VN5edn+wQ6Vv+sHJ+5b1qnPQnqKfFCRef/pO+BFd5T0U5gmYzlQ/eRDW8S6tWS6ckmvhFacDSg1y+J0W/2bErlZ/eYtkKa7nCmYTPuVbpd5KbIWz4HXhLIdDZbYT7LgSxOPWmD2k0Xilf+0GEW30i2+9qcnZaToCZbUFNvMrVkTviwzMe9Tq5DXZLXu3ovfnZZk9CegM6Zo6SK7R8vaS2DGPtvgzaPZCSrJggyUb6799h9RghIeSxmRM2Zs8OoeD9SFm1XVyuXElCRUOAqClucXboyZz84LWlyGJ9oz7qtf6uvUY1m3MtjMJ0iwzMsvpFY+McFQWmaz35sBSdrpIqwEoseJfW6sT2NIbANftYLf1c1Up3b8grOXMd8pGix+PXAzKdpO+vPiWHMdr1W+s7nJxgxCyBmIj1yJxVkVZYd628Bb+XIgtAj5PVM6ZDAmQc9/sfBjkUy7aiaDnFsMesrt7O8mQtrG1+EizFLACu1Gy67FA1Tx58IGXobaDZhvUJYrPsnfwD6Tbnlfp9767YYr7EfohARPEfQHjM1y7i+qxotO0Kt/tlRi0osOWFvNIbiMNS4DGsrdzYwtTA6+7wKjKShwig9av2Tmyd5qPuKlYuoSh7ZUav7vyE9HEwLp+oU+Elna+Q/945MjMXRrLIACkgObWoYGw0RqQkUA7+l89GKevITLaDuKkT+j2ndQCQiVuOeQWYepqS8JN1QDsR9oUo0T4EMwxGHRyjgvKl8mzPcVXj8KFNF4XSa9ySbhte9EcBdoOocu/aacxBZee/H8O7Z90Wkmn3pDk4vIdUlVV0mpmXAvXx7JR+ZIGqY/H2FoG27je676AtINy9GDAvmRtWAZ0NiotbQNcXqUf7U6YILQcXJ/HDKMiMJqHR+nen9yw3H31GJX5lseIN2eDGpaTBkn3BDjdA/UJRscFhbLtCFrfXv4HZl+pvgEo1o2GNvqIhedTrt8KAA0Uw62WvymDe7611QPoyCZYh4eG75BVp23MqjSYbaBi3MBvRxYokXhdQtDKdx2voexTbfaTuAiGqJ6XdvpPKiJOvTwz1QIB8yvPfSQHKzCz6YMk81nILsVqx8ye5gSBOA7BSVa0uJgJvRr7IJotcy+XPEsLVZBGmpjgcCYAxSO29Dzzppe6OWKY5H9zE94MO/K3fDmjJrnzk6B3geo2IHK/ONs88YjVThxzH2spqQ+aq4bGejAk0nByF0SCF0h1lOM5yQhLdUg0NTmUebqA29zbMbDHK8HgM/4cF5KklOS9Rdw7KKSzV0EXebfxznNjDXPb20lDJEoUHWIN5LS8ZL1hvZ4Y1yjqZSxi4J/FcdNs09bJrqnoSrK/fdc9Esh/8PfcFzTm5O5vCgfw0UAUncMsEyC2UO0xSUaoUrXuO2LRTNKTxBH9rBX4tvEvqSbeagePRbzV4vku05iBcYRVJdQq42/EtNTOoZ8SzyuPhItRE1ki+v1Hwv92e+ouYqmfRwx90peyeej8WVR0zSEIirpkrOvjykP7KJ8dSdFHQ/1nrqvfirSnu3gqcCe8YNBd2K352tg5XtLqXsXJ714ZMXhwriAz5TiYC94ttDTL/hBABDZKVtfc/Kcp3qb8AX5zSU5vTn4n1sOiMxr5/380JXCqgii+twfGe+t2+lNdHZDAhCGxuJcN5eqZUQw/2e9Mu8ypo7JroTBuJZg/xx2G1bJ9mh0h7Rna3HxLx3FD1yV0t5KKv3bNUu6fGBJt3tdHITWUSbYrqmoFI0kWxPXYKZmGhym+ilkGUzvyFy5SFE/X2+HSx6e00PjD96L/3I3+Wht+N7otpOYWZ0/8vIZxbpMdFGvhFkRtP6e+2I/o7sWbE5HOpnpoMx1Rdk6/FPcLI4NClVytwsoGX+Pv08bqBR6P1i/jMXws/qf4E9mW+svQbe0n/T9YXq/G6xRa8pDv2L3bp9MWmHwhk3Uw=
*/