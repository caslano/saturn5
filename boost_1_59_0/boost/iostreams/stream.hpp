// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/iostream.hpp>  // standard streams.
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/base_from_member.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename Tr>
struct stream_traits {
    typedef typename char_type_of<Device>::type                char_type;
    typedef Tr                                                 traits_type;
    typedef typename category_of<Device>::type                 mode;
    typedef typename
            iostreams::select< // Disambiguation required for Tru64.
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                BOOST_IOSTREAMS_BASIC_IOSTREAM(char_type, traits_type),
                is_convertible<mode, input>,
                BOOST_IOSTREAMS_BASIC_ISTREAM(char_type, traits_type),
                else_,
                BOOST_IOSTREAMS_BASIC_OSTREAM(char_type, traits_type)
            >::type stream_type;
    typedef typename
            iostreams::select< // Disambiguation required for Tru64.
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                iostream_tag,
                is_convertible<mode, input>,
                istream_tag,
                else_,
                ostream_tag
            >::type stream_tag;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

// By encapsulating initialization in a base, we can define the macro
// BOOST_IOSTREAMS_DEFINE_FORWARDING_FUNCTIONS to generate constructors
// without base member initializer lists.
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              >,
          typename Base = // VC6 Workaround.
              BOOST_DEDUCED_TYPENAME
              detail::stream_traits<Device, Tr>::stream_type >
class stream_base
    : protected base_from_member< stream_buffer<Device, Tr, Alloc> >,
      public Base
{
private:
    typedef base_from_member< stream_buffer<Device, Tr, Alloc> >  pbase_type;
    typedef typename stream_traits<Device, Tr>::stream_type       stream_type;
protected:
    using pbase_type::member; // Avoid warning about 'this' in initializer list.
public:
    stream_base() : pbase_type(), stream_type(&member) { }
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} } } // End namespaces detail, iostreams, boost.

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream.hpp>
#else

namespace boost { namespace iostreams {

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

//
// Template name: stream.
// Description: A iostream which reads from and writes to an instance of a
//      designated device type.
// Template parameters:
//      Device - A device type.
//      Alloc - The allocator type.
//
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              > >
struct stream : detail::stream_base<Device, Tr, Alloc> {
public:
    typedef typename char_type_of<Device>::type  char_type;
    struct category 
        : mode_of<Device>::type,
          closable_tag,
          detail::stream_traits<Device, Tr>::stream_tag
        { };
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename
            detail::stream_traits<
                Device, Tr
            >::stream_type                       stream_type;
public:
    stream() { }
    BOOST_IOSTREAMS_FORWARD( stream, open_impl, Device,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    bool auto_close() const { return this->member.auto_close(); }
    void set_auto_close(bool close) { this->member.set_auto_close(close); }
    bool strict_sync() { return this->member.strict_sync(); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
    Device* component() { return this->member.component(); }
private:
    void open_impl(const Device& dev BOOST_IOSTREAMS_PUSH_PARAMS()) // For forwarding.
    { 
        this->clear(); 
        this->member.open(dev BOOST_IOSTREAMS_PUSH_ARGS()); 
    }
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#endif // #ifndef BOOST_IOSTREAMS_stream_HPP_INCLUDED

/* stream.hpp
bPzCqtioizq+Rpfpjy3RD+5POGW3iuyyLIWsVYpQSCJhGWQT3y/L8Yj9YIosAJs9iWW9u3sJGFALnYGsXK8e/l0LMuzZ1XMMD5QMaGPoyxnwfvSEAkouNmSeUdEZOJZk8JfB7q6MZOuEfR+kCgcEmAFhEQlQgiE3fYl7x0FQasSfwwHSSdZA73HcRsETnoIhcCCdnbk4yIqTMTD6q4+UvcDTYegSZu/JRv0obDKQbFDBH486lOXUGa7fntk8jHKHM57Vj4p/vGSHoK3Xw/CDYPw02/TphIlF/90waCUVjf57/lnoZ6E+OM+UhWOen6rBEV0nGMkeuS0WX2ai0qdaaC2UNYBWUu8A3sROFVZy03kze5j2WB849Gp2fqGurGoE/jvvZD87/DQi2pznUmi9VzVIs+UZ1K5WKHlIhHLmSP+0Fd7PWI2kZW9CjE2RIsSPjO8RTyzNl2Nwe4hL0hYPSqEp72hdfEpKVH9emO6YyVRk2Xgj57tPMGavqgaGl390JjbgBYcVrZ4VZ/RfpEKSmIbcnN3JqqSERoADfH/M9y1VcYt+I0dIXwseaAGdarPHyjTcE+2HpW9XwU3GjOXzPcbgqrZXqdBMM1ip1qaoPHstVmT9Mi6zejXnXzt4jy9xc4Lpax95MErdYzMyha7rzWaHYaUBOFD8d3M/PCUN+bGUmOFniC/f7P5VD+Jlpcnjvu28PqCZknQWDOoDQ8C3zRaLFqAdfFoCclyvINPePU7F/HQ6F8MMPQX9EtSE7lUY6oW4Ol62xbwc1TH07shLfqfwpYfUSgahHndQy1GSulxZamN9ILisg0/Nc55Rb2H5/ujPOKgpd7HqMMIC/OF/5T/kaGUvmVuc8Sn/FrSXPHnrtbfS/iF2DO7ll06D4FVamDOMqHXHZhTYmSPlrZus2e+81/ouY77Ba5PWgVKtLpk8iy0Ew8vNv4XC3LOzP4u864WfCBvvzGlzqLyYHusBoIzGIOR6nwjn4ErxOLGlviSFSkTMQA6WLfN1Ion6zYmkjadJqkW7UINzlWjw9cyu5S9OhBcQdxuipR/ZhKsyGFXB/asWrLQSv5OYY3D0nji3F43/SDIJ6mZDG4AwYCNBgm54YJN1rxjixNGpRVxRsNs4r/5gle5xNyNgTQZMvNCs2bZ7ZAvJfdEfDK5iUfvLrh7akk3/Qeon1o1SUe+QmvEuO4ufXSQw9QGYI9BONJDgsrHHLAvWiRvQnoAWMhEKiABBdX+ZPM4/zlG9Hc0XFkOQgZQH8wF4cSana7XNG/Vcc6f0OBM1seovIlIr+mWWphoe6poG5GOokL4wLArmNHW/OqXldzCUMn5Nxa6tpT9C9G6ZaOSZEhuWVvRifdhQ+V2w8y45TViuGtur9Acz6lE4wVopN+WMrDb3O2GAnqVByIQ9dbP/VfuT0YsAmsXqIhDKFAjUAssB8/EJKiQnipak8+00abFFt6Tz8n7lJNNeIeX2xQYc0zhPWxIS7GPdHFBpKcUZ6nXiu8HCZJqIHLdYILtEpha9w+snDIZzEvrwaNVWW7VRE4GbzI2DahFlbKAbbsZMISnAHzzzWLRnHVglWmy39iXCmTeBiPY5gnpRnl1tLQoGo57fKehoZb7K8TV5fKcFVNomISLKTQFLIHeTOtV+N2wXFHoKVg7UjM1hU3bJdgIrMPW8MSgRV91wyhsBDq0ONCcsiM1vzpG0v9Ln9ZxDVZTQNJvABgcrYxg/wvujYtkJZLb228bwPBDnKPTGPid/HowEImpz24/bKB634OmxmqLTyHivlSSFFKk66Oi0MRc6Z6PKoh09tYS7YEd5nfbpZ0apZgdEgfZ0QnXSBPwoUtCVCRSwAHDPEu1+08qRmZSTCawhLWl+Kebp2NnpTf+O6EuOYbGVCS8i9dpe4nAukz5p/XYjKX/m6Eti/Y2lOon5elTmVF2exTvXhfGWkmC+XeplHXioj3o3tkSYow5desnjn4WIvPzDZiUyrPWXdOscvUCeZQNc5eTS3XC/lCB5U63vPypmS19g/8KxYzwtn0o9J+wZYdX8dfA4+U8SFob9JgDV6A2QIEWOPoMvjgckDWFCgw05msUZjWYaGN+00IEka8ZS179g+nA0N/u3kzaqezkSBvuufO7F3Kb5YI0U3xh/R5ozb2OLcDtIZVU0zW8JvVRqy0iGhSH6GGqK1p1UElQngBTqvzO1NUf/faAlfaevUBA6WFmB7G/OtAbe73rdaVMirVkJO/NkPzBkVLYezSoUSwSZqNgSve4SzSxo7AAyIdJEc/2Ncg7DWkukTLagejsbeMUo2pKySQrOa0kPmROVUFIYLfBjSYkdBojTEdpoSI6wwAl7Url/LO1PsktSypx4W5GbuWaKL9Mym5gTLdkikX7PWogiVVQdGWuoFCTy7B/fVXWdBd0TWQYNI6hZ7krafDHDoH74CUefr6AbcZzUXOTwarHG52rnETQnk02JAkL2+6k8f7yx6ShzHCgFCpCBqIRx1GCxAgwGAPCJ03/girod4kgPOMC5fklgTivHsCo9VDtsfK3t0U61qZemAotZwfK3XQph01tNS7MNDjUCgAV4+m8UT0qENUGEMVILNWfpRKMRACzMXQ+QIcZRCuAhFz/mUHH8g61mzuzgXAirgAT6zcFqmcUGBLUDoN0XexZZKqpipoZVpRM5tySfbLVW0dl59Wh69Te7JodbOiOiPmYOnySA6Yx+JN2Dc03PambfCk2jCZmwpCYvrQcl83wUzvYvTk2edE1B58UfyC5SLtbL4s8G36FQZl/LvEq1MGvv6yuoPzUqJrowqesciMs6JWp8jKgKNuKRmsCk1MIyc3LUcJFRuOjbqlF4x2ff7GvHe/Ofkf/c1owyFnJ2SGUxPqGFVvOFsjMiJaSj0gdKjmwlAiUYhMIFVR9MARp9B5OVvM1RdeaNiqgpdcnFwnIVLJ/UEPnvXlUFg1KgYmO1LE0Ns8rVN5pWN1X3OBxEYsNm6wmZAotejHJfrrgBAAC5APNgRP8bKMPsgCNcZDyOj4Kvb+TxcVDrf/dFQiJRM92N2HNCQAmlT/4JAdSAAXbO45FaW0Kljb25OLfITXK3Lq2+GZrwUtF1KgjqKdfBkmory48p/bijsvk7yPKVdgea0FsbKMoA7/b9zYmqUUiEgZVQos8OADGfFIPqL7NqV95Z8rFyDpNzNF2JzV8opoEvNWeyUiT4rV0NVFy2fVUoqFNlnDvRqJ8cLMMeYZspHSwvD5EbgqoUZ7KvDZYILvKmhZZ/Ls95TJJOVHR5RIs+/E7mRXxetOCT++7BywDrEbsNEsxc/VT6tBtFy3L9EzjRaYvCT/E9+wJ20O7CsAl6xCXr8uZ7vcnpg8w2GjecMob5U6/YI98kF/GKe6k2W1Ewv0B5CBIooy/JENUqSV3jx+2wKiVc9aUN/v13wiCJYUg4Igc4exyVCkFDutQqA/iyhBSfIG6aLHhLGWeoQ6I9sjJB/czng/KUF5mcHch1KRjUsbRLuWSP0khEfcNOWOGFKbIoUmU67kURZlxNqqZwgtJt6Wh71OqcF8tbTezj30gcD4eWXRRB3YjXCqkXB/2IXwK0rRIw3lBg7HsO8jgkAYyoRLq3FMo8wQzv5MaLCq9hBSUITVVcsldwVS3qSdFLX+a6JsKSc3mYAcg/R5mJyeBu139WgZlik4z7jb7wb7X6TadfuuIa3jkxeN9kY3hYeL7rWywgoMKDl5CCh0b4fJRUGMrh8d4hBOoyat9R93OQXji4aKTg7SIwNQAE6B/gmENMGAXt6nHut/Wz4DNqnRoyLEFQ5ipUStKiBklM46FTdUUzFS7pZcgtPyb1srcTYn9+C5dbFIpkSBgRhLC/yzp/UJCdVEu18IcoALIiZGYDhdNL7Ip+rYdlSDqK4XmmGiii0gqStF+cqmdNIy7UAeXsMLKMhnUOEuTarClT6CJKjaYDQUeserrLkBbpRJQsHokhlfWbwLJLYHxlWCdZ7VmPCvJ4ZziiYKQCGW5D6MMgSxKd1NkENopV63OfhtooGWaL2JITVK7K8m7ywCqRILYOmQjlqgpIWz1Xoc1Q1V1eg+Gl5HssRFkg56YGbwxIPxpgOrBO/qJeuc78LaTnILYl21q1nwn/Smn8FvtWQcn+8JVhDt7NYNYXGoeZcNdD4LVZ8xru5y4CaQVDiUIKXvIR70qpKgAQIRMoVFJHO2sA+gGjeodx7QOLwzpHucNsvK5D8WfWLAJkK0cDEb07Bo9WS9dR51MK983XPBcGPv3cP5lc43x86De8Er/hlfxfeJ0zIx90taK0uL8CndWF1EJl/EMw3T9c2mKUima+F3+s8ht6b2EZbYBj5/ak5nhPJy9rMQJ4gUBn5q4Xj5L+6OdEjMklDBhtVQpdMeEX89yrVd6RCaUPCY7OWdH/0HrHpVeb02GglgUbyYMKNWHV4rtQnF532IM8TjwU58kb8DUoblLI80ripPJoDN/uO6vxzbu44BF27cYfkJfMxrvDqQTtznTk+Zo31+maA2qSae9CfuOFMYaIi92oomCIUvoPzVePlQORAubEBgLgSN9ajohB8kQyyFQ8inmEyfbpFFbiREUe15vWBbtpMB/82LVonW72vGKS+lKtKjOgzoBa+3O9m1xiU3aBD7bwTf1jun/5p86fnQNP/4JXofMZq7VRyH2gchZirKI59NL7s7VCcBcRYYU97qRhV5eJ4fBQ/DDy30HrMrIhQcxg0SosFUotzNKlgtYR+SRBEU+F7BpqGOLhUg0pFwV2buPT41QoMpiVQuQStFg29whsGWtizaUmzOfIlVVc7Mr4iFwVE7MKm+pQvWBW1xcbUr9xVkHzxo0nZ8w4NA7XpKi1gUpNifcORBxu6uycnMqpWCjx1oV9eR5u3RbyOYWhiwdHs/o3qW1G9cOKY9i6N+tGk/iJr8pwArPbNs+Gabq4MytH7tFWdSHyqwHLgPNiYCMwG7vZSRUAAiz905k4zAL3btOdUFwqr2pe2JtSke4L30uYj8a8cFgOL3qs+zmt17glERATW4l5BQwhUHsBSAFY9LmlLbsjdSOuhToKKgirfygcb31EP8OZJTwnMzWHgY3TBuF8fezHXWdv8q5isfY90zk8k1l8HKupjP3FoKq3qhvhCADQ0UcAAJD5I0QPeL81jC3DGRGMAnCfmwGitBKtgsbC4Bl3lqfiawa1yb/RSPD7Y3LgOJxIWEVRGAOBwG227swSz0sBIsRYNRG7N0MV/jJsSVLf1piJVBZ5sJT0+JhfJQ2LabiUwr6+oh9agRwAahjEdmq7tTQ8c4a2I5b00Ob6xjf9AxnH98HApnnR0r3Bn+l5xGPBBVW3VwBHWkbJJ3WFrCRMwimVsjv5xtRropNATUhTGJLRAezb53HoP3CLckSSHlb12mB0xDsl7+A8rjFabEfl4Rj1zb51bUWjIxVSIKGlMjaAACEFAhiECljAMm90gQgQAyTlsAkPsWQWDNEuiHFd710d2nZXxYt16WIX+0VJMsmt8AJB4zG07P0XdkfHQ4m32eiZ375HqdZaYaZBbAhmlcNHmaYMxqVhuP0LmjPuSMgZha5EWgG4WSRKpjbu/49cw8j+72cH1jEaYRKL9vsKFE/sPNBL8Yzfi/JPLCxWL6z6OSvVqdNloZnaIZDJeew365cQXjQe86peBmiI03TqXlWVsL4kZ8RLku33HED42nP6caZj4yd+xKaohzQVkFfBvuBzvrlVsFZDoWOy5Z+SBN6fXk/qL4FLhL8ay3XIT9LNsS/nzA5ycDWWvLAWxqq+bxWVGhm2e36TWBQFW40+c4fc7MJaT5UhX5DsDZQ2piPD57wCfseXsP1pxOz92H+2FQ7DQjbxEwFF9udiixoy6dguKBRFyMaiOX57f20VxgwRhIA6BCFAAyUpAxu3QiyDlX5OHehHj983jH+L9NQ0FsgCU0yZiS1oYr/cUP0junSYnF0Nii/ZmKrKM9xfYivE8hkj38jH090KMSIHFSDSbJGCUN8rol2QflE/2phxW/B6jFstrIW/htv6+KmZm8wmEQDYrfKuX2zNmfKNDgZjerSdwRMz/XVRmHKbpFWKBXaGhXXWcuNQ2vazvcYIuiIlBsQw7LLGUgxviO67yLEZE0p5WwQrPoeWTgiX3mWnRcyzwua0UyT2nJi1UYrGu3MxS0IDTAoqX1XmzkswbM8eaJunb+VPCjmSjifYXkm5BaS1Mo1CkGFBhBHBWmBKmgmdFiTFBtAVAnzqBIbaOl5Ir3bV/OSQamTCTo7Km+y+qzZ18RJWXcibXM3fHdaciKadkUKq9UmjSErKYM5cyslQ2z1rjstbuYb0edHdCPm5vcs5VcoRA1efXd/Zc9ZxqmKaFxFeObyDPwAlOo3871T3RymEenWm4FnLnIKJkZFV0Tzm3WmSVzkAQzB1dY+tI35zuRhX8YZ9qw9G71VD28FX22DfVF2WkB4GicVsMesbgGe/r620DGEuoD4hCAF1Fy0SVHU8q6ohq4oymBCtPrvCOnA2oF9OJOpQ96VfXxk34YaXsG6vB4cyoAQ59o+iWvzy6z5hjTK9X0ZGDLRPF8fbWad3nVfNqafQmvKSAaMOr61O30RgKMxnkjVy06K8sUYYR/8Y+sb3hpcXXJ76POX2KltCU6sT/8r44f4i65hyqiREsam7wuO0zaycKssqoaVu66iVKeCCx4C12HdNS+FT6l/bgVpD6oy4rKteB4wRRwuw3HIjLGULSRiJU4kSJ4bNLGoRzbFZ6KodwtS+M21NnvtjKQP3XF03a53mnX+jBcxYXebZi9L+QHc441VOKOXRUo0TOpCdyphEA4QRg7fxOuLUqgU0ATUAHiPJCAGZvPzcROOi/L4JrlcrIOOyauby40IoK1JSJF7vtWQSFnlABkc8TcuaJblyxCDDZGKzCkaUViqQOvSBVBxmTJsJpAOUR9Q4S9fK3l4+9zmnmGgaYs+7RCwnOvykwNRX5apzirSGD8Ufpmyu1zGJFHq21kwi/VAyEP9IwoYoRGPgwXnUBcPPFw2VfKu9orEMBzTu1Ub8WvaCqMvAAQAg6ASzYDQMuP1lhrLZ4CC+kOY9su8iHuid0eI7e2iYa+i4KKfpT0TZoQGpkuO0fYpo5vsg1u/lS4MflbCoxnDxvfZwWOuROMBOhyShHiLtbOR9jeOGX7WqYJVokwroE6ksH9lJQuX0E5DkcpdHHlKgQQjFU48uZkIKQbK5SfQrC+eb2f25KO+sWwQ+YmDFgbTaSEuk2lEM7YX5bHSoQTz7lNmJObKgLa+VyQwFJCmsiCVKB4qcBOql/wiBlPHUAlPkCjaPowFr54H56crahTtZzJ2TLDUAqqmwd+yb0j1y+1f7ufi5gP9TmVN6EdRW9CbTkywuLGLyMM5pQZng0oRhbG5Hu6wpaHa39B9g7V11PM24Kp52AC1YT8Qapig6GNHLJaYKeRhSBG3/A9h0Ombnsd86+rL3VlBKTfxPEPVfhKtQXL9t2i6jqD+uMtXV0K2+nD/tYb+G4pC2h7hmPvicaN80/UsPwuli97lqQC3/uqTQSyCWQVYe2ksB1vuQsbGUCS924sipwzMGTqmUEpIN7WrKQOFcoqV972Cwyns8bIUqGHHlX10gZVD3
*/