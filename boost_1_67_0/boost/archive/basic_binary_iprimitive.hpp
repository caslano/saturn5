#ifndef BOOST_ARCHIVE_BINARY_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_BINARY_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#if defined(_MSC_VER)
#pragma warning( disable : 4800 )
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_iprimitive.hpp
//
// archives stored as native binary - this should be the fastest way
// to archive the state of a group of obects.  It makes no attempt to
// convert to any canonical form.

// IN GENERAL, ARCHIVES CREATED WITH THIS CLASS WILL NOT BE READABLE
// ON PLATFORM APART FROM THE ONE THEY ARE CREATED ON

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <iosfwd>
#include <boost/assert.hpp>
#include <locale>
#include <cstring> // std::memcpy
#include <cstddef> // std::size_t
#include <streambuf> // basic_streambuf
#include <string>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::memcpy;
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>

//#include <boost/mpl/placeholders.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/serialization/array_wrapper.hpp>

#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////////
// class binary_iarchive - read serialized objects from a input binary stream
template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE basic_binary_iprimitive {
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class load_access;
protected:
#else
public:
#endif
    std::basic_streambuf<Elem, Tr> & m_sb;
    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    #ifndef BOOST_NO_STD_LOCALE
    // note order! - if you change this, libstd++ will fail!
    // a) create new locale with new codecvt facet
    // b) save current locale
    // c) change locale to new one
    // d) use stream buffer
    // e) change locale back to original
    // f) destroy new codecvt facet
    boost::archive::codecvt_null<Elem> codecvt_null_facet;
    basic_streambuf_locale_saver<Elem, Tr> locale_saver;
    std::locale archive_locale;
    #endif

    // main template for serilization of primitive types
    template<class T>
    void load(T & t){
        load_binary(& t, sizeof(T));
    }

    /////////////////////////////////////////////////////////
    // fundamental types that need special treatment

    // trap usage of invalid uninitialized boolean
    void load(bool & t){
        load_binary(& t, sizeof(t));
        int i = t;
        BOOST_ASSERT(0 == i || 1 == i);
        (void)i; // warning suppression for release builds.
    }
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(char * t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(wchar_t * t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_binary_iprimitive(
        std::basic_streambuf<Elem, Tr> & sb,
        bool no_codecvt
    );
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_binary_iprimitive();
public:
    // we provide an optimized load for all fundamental types
    // typedef serialization::is_bitwise_serializable<mpl::_1>
    // use_array_optimization;
    struct use_array_optimization {
        template <class T>
        #if defined(BOOST_NO_DEPENDENT_NESTED_DERIVATIONS)
            struct apply {
                typedef typename boost::serialization::is_bitwise_serializable< T >::type type;
            };
        #else
            struct apply : public boost::serialization::is_bitwise_serializable< T > {};
        #endif
    };

    // the optimized load_array dispatches to load_binary
    template <class ValueType>
    void load_array(serialization::array_wrapper<ValueType>& a, unsigned int)
    {
      load_binary(a.address(),a.count()*sizeof(ValueType));
    }

    void
    load_binary(void *address, std::size_t count);
};

template<class Archive, class Elem, class Tr>
inline void
basic_binary_iprimitive<Archive, Elem, Tr>::load_binary(
    void *address,
    std::size_t count
){
    // note: an optimizer should eliminate the following for char files
    BOOST_ASSERT(
        static_cast<std::streamsize>(count / sizeof(Elem))
        <= boost::integer_traits<std::streamsize>::const_max
    );
    std::streamsize s = static_cast<std::streamsize>(count / sizeof(Elem));
    std::streamsize scount = m_sb.sgetn(
        static_cast<Elem *>(address),
        s
    );
    if(scount != s)
        boost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    // note: an optimizer should eliminate the following for char files
    BOOST_ASSERT(count % sizeof(Elem) <= boost::integer_traits<std::streamsize>::const_max);
    s = static_cast<std::streamsize>(count % sizeof(Elem));
    if(0 < s){
//        if(is.fail())
//            boost::serialization::throw_exception(
//                archive_exception(archive_exception::stream_error)
//        );
        Elem t;
        scount = m_sb.sgetn(& t, 1);
        if(scount != 1)
            boost::serialization::throw_exception(
                archive_exception(archive_exception::input_stream_error)
            );
        std::memcpy(static_cast<char*>(address) + (count - s), &t, static_cast<std::size_t>(s));
    }
}

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BINARY_IPRIMITIVE_HPP

/* basic_binary_iprimitive.hpp
Wqh1ZemWCxUNCkXsksIYXthaW18NnNMENgKSUq4pB8AL/MENDqo2M5b9h5I4qlADHODTdqTpochXFSZErygmCFFabyiEWihhZH0EFQGe0YfQ/hZm6k3VDjNX4umT27AJc7LajZQruabNFZyQ2oRyTORfBq/U3R7vNzdnxH7qPbMUf9bpvqCC7hTau5+Vm4AAECu4oIZh5JilAQbCDOHY2NgVhBivaUorFQSdc8aJhBCigNEIbUqYymWZDOmqAA6GUE5pe2tra3dxcXH8c0CmiE/i6b6AAp6qi7u5+4AAj5bw1PKmfpx0oXwxsoFH64sUSuVLQgxYgyilG1oVhn4ovzvBJisy8SaqtWq7IsTG6f/ePbeCAr+JS8CgEcCQeySkyO1yv1vVAx2RowWv8YMV1Ky9uI13GAY1mUgiLcqiO2ecFS/5r9NJVvvItWdnZY02jAmQpisQqHCMXzcjg7WgJd0aCyaiqdAVa7ZAQd6gIG0WJiGkxOVyu7txDtWNCSZrE1C8MfT/ljL0TEc/JpBfFKkKqNXqeCJSvQCp1Mt0C0Y0ViiXxQ05VMKhaiUYUJyMRilYeAYlCAmcCGVVUGKEUJHk8UZC+qKDlCRnJxfDPytb6NjxHoQg28GX8mfdENMRNDjPYame1PX4jziWD2crVJQJhNfjK+xub/PAId9xqRhE8IZUaXY0VyGAHJRTbXcFwIQGToZSkYQA5g5+F1t/vd7gakAUFSjwgnn9lp9dl1TtgbrMNL4W0tbCkhAYmxUhBC0ESf0QUd3z9COMppkulcpix5tqvWLw5B1Ag91QobAoK1MWa2KGnCYqLNBmy3YX7chzdbvFSo5cz3ZypbXJMJsik1WuqOD6RAx0oO7xJYEtBrEQkNQsV7vJKwhZeGDNU68JK3S22e1shpkazT6kLfPen9dAfL0hpKwmDjsXL+EhAwVNvpNQnXidg8GACtHS0h6RyWYtR0BBXXwHpeKgQKm1Vo2DDJUQZbNl9bLaZ5yvzpA1GvZEKhC43bH5Wnver2LgDUrhm7KUIpWDOJ8NVLYfYQTmYqSzsWVNXjDLnmwHy2wMRxJxqD7BMa6Ez7KXvMBCMH5LWaKioHUKa1BQvITj+3nQkj3ibrXaXgGAoQ/csbDo9AUkfNu8MzZSwpnnmg45jjsn+HIOAz2gBwvki4LSAsLI5vF0wA1VPNRPLcCjRukEFabmxTKMtI9ov2Xdqs5l3Zrnse1U5TMeuNpnNTpoZOQF9VsSGGK2c/+l1NfrIEOgBccJeVCIoOBkca5TCNcp8/4xKHsvM5b+FifL3iw4EQDwCatPxoTUvnoh+7+HilGCEVqO6EnRW+QA/eADv9OBmN7MN4zLHPTg0vzso6LZPortngE99tr70dEHdfDkc9x294mOOGykPcU0ajaZyQ7yibm24gUDCZUAFTKobwJ3kHdyya5JUcPkxtOxKz6jsBr8YomQFCNwwP4JTMBW8YOSB01/AXgDFJ0rXsbxzi7j+ydZcty4IOYVmkkcFDiFhpipK3BUnPFNjsZivxkQzcGKQ03Gy3m+xt3Bs/qz+x0y77nWiGaP5QTw+F13zJRH9AXzwXINQ3Kk2XLmJKVSQgGzhhpwgBbB9wht6bZlz47hs/bM1bG1IIDozZdT/1OXUFXLUHENlVwlJMOQQL2paGzW3dHVWNwxF3J8xs2QTn0OkS2ntxJKnOaMxtabscHyGpjrCdgJgISZo6CJNffvZ8n76CWEnYBCRAmR/MdueRSVTk6ybfF9WVF1u13EAQca1xxwre6M8IyFT0NL+UEVsTu8UhEMx2UBpUZ4nJPyioMCsyI4aB0KtuO8wWm//vWlLXOl655x3NlSCjjIMIEco+M4X5113K6VXF3DVLFpFTjxqZVMJQDhVJo5FXz0F4envLgDDQsYRHdRnPsTrrrdU4CwBigHKNPcmr37dcdaM4/N2I3R9gzD/PANL6wxi7cIBGBZO2mbMZ+cYtBgQhR/b7Neb4iu1uVxeuOwfPInbN+ocwSDhqZdNnLatAfTkMfz+30XgIEuHE4ml6MRTIhaV/t6xapz4EBdozBIwuhu0fWH1/TV1sfmK89nN1q4S4nBeQaHEDE87EjG2SBIMIOS5FshxPjMZKtb2lyzlHJ9w1LizWjuhqHhSCzdpH4Bco3LjxfkVJjp85FaCuacMUBhqia0wnV9mAAdlLzebLmEZ8N2uX1sBjGhD09GH5v8fb1X5aiAQE71OIr9wgsRprIkcGzvKVyZtNFkXsSYNd+vNrlSa2AR2TK4nAcv5m7Dzu33adz0lZYtK6udbSmyb3lcQEPF2btLQsYqFI9cyFBSdHUTrSKaKckSi057Tp5U6uKeTbm1YSXV1vYpzBzlyDupAZ9hYcuc+/fi3HTb5283Gc+zKfPzDms2yHmWncCMMi0UlSO3yWFpPxhQPrT4n01nM7zo8Z1Ko7Utz5deuGclhAnXKXrUui+/FeQoBlLsgxOS20+43A+Gfw1XocKhwoByXtWAi99lrcu+4f9wbwIXrpDEOIoHHzLJhiW5spYxGkVBzl8wUVL9UOdzMmG1yilxD6xPsd00FDr4fcKYVd8k4E28WJJ9eslnSabvGUxZXUWL7XslglJM/xXBKwsjvlqrO0uITldsLfztDd09HjBixrzAM1mGggg54iYoh6mo99GeUqVCqAtxhoUCBh1GhcqKVuyx77Zr/T5yl53zdY9WUGAIogqlPoq8QIA6NyEWfzCWbzCn3GmcSrEdI6bUAXFAEQ0PWow8WGuW912V6Tnt/HdGiQJXaSMUxCVtlGrd1oSj85xAHNdTbCiMDgDg2bZt27bNM9u2bdv2zs5s27Zt2/h3b9IvTV/bpGm/5h3I3zA/mW9BdjVRRkA54hUiWD5j0B1Jshv4k8as4ZwjH7IIULG090GkDOUjuFc+HFl9PE+4j+sfEHKRk80TLBxHtVNZq+b3XLij2UnACLsLwBjfzuiII75TZr1bTyW+tm26JPq9Qf7NlE7epEBlRHaj6WDOVu/GGIqTF+c32V9LvNm2eIdM23uHs6Hrq8JYFgJliYcX0cxm1/TuBQRNbBXj8FBonMZT+dw4URXmdjv0COXF5KYaEZj8oGdjfjGhF4HzqH7NCmp5qvuQOG3yPa7gIMEYvhtM5/rsmNM44QBJDaevDSoMIVpBNxr4dll1vn1wuJxz6sWNW82cgH4PCFl1wPRBqjJAGYQ7pRxxbWB+T5warPK2J1zXwgAC9gXj3AtC7sm6XPyVK1rQxX9fJqcU+BOBwqoNVkI2OGyz5PflK8Tv4xGc6sF3YufCFWqMJmKtfTcanD0Fj3u4iis50qRr3ZS1QVKW0gxQt0dDVmbGpBGKjy12GIUmfFVBsyoaMZWqWFRtVb5Sh49zvGl7wOTGtd5antUu5ZOSsAUbI2bkkB9kzSEtgC+QO2QpnCaYZdd4paLkokVC0ut0O405F65/rYo54oARsCzjWo9IFC2BD6S4FcM3wu781eDOxrxltAGhd1trwOLJNaAPQeiq04P4DNLRCe3OLF9bYCAvIjdirxDor0TmK+C65+grmTsjkHeA0XR3XQACLP3TPaML2CcWdypn39A4op3rr1+8nXKAVSMFvoLyg2VoOMywYdLmdpwd/5TCBi7xGgWXOHb08uVLCTNiIQQquDvHKFNlLkgvxHVo1Tx402D64NCbJ2tqx4WZldvXzgSTttOoTr5scD7EJ7veRPoh6LPU2+ZgxJf60WZU8O3BNYH1zbuUxptJ83ILPFwcr4hHgnJOqv534wiMDhzRthwd/9k9OcGaOavJ61lc40gboyWHX/HZEhLeuReQ8bUXFpSupaWy14AhCiDsW1BgtXHv3wl3/8KzTP0j84sZEPsuQ4bV9a04SuP47pM2BB6TiCWyu9R+Ckesx8iqgHcoJLkWI118Ev2Cnl3XgkHuV+EPs+ZuyOYwBFEeU87MThqktGtG38EgTeiZDNPht0EuPCQi0iXOCzgEh6dIUfvC1dvjthU1GrxaCoJ2HEOQ2+McyYh3458kmiaW1V6RiMTWRrPs4Ev/JKcAdnxtqlOniUAehrz+DYGUkVRED63P4RuzxJGvQSbjdxpnTh0jGmxeiEc2PYzYkZDIz9gQRbTia3bFVbxSjm+6znhScfXpJKYj+nrZcGbhOpyaPX+QWdUjJ0Zy1Gw5GNq/VA72h1+pIXwv6LV3TytWLpbOKk3+mJJ/qCZSR3FmYDR544oYSOA4Ou5u6BZyJbhsOZLa/voCTKzqntktrF8OcfMOPN+UUJ46Vg9j6bTyduY6ebkDsphW+C8w/rDALNxXRMUCEE4n7OP45kKEzdh25ECFDQyH2w9AgbggqBnq2XpJDDwp1z96ADahKN/nbGYCMuHNdPAi1cDrhyey66daZuFOPOeRAPyUgCWd9XQqCoIfpavCjxyrYp5G+BSn6EoZT0zioPGcEUb5Z2/FF0zF4Ok1NDD7GnX17KEprsLFNEjl8oD0A4ZRUeCZvup95wfbXmTm0FEBgbTiIuCxWKos2muzR1droinmSqIQwaSXaf7smOT2CB1nIPy5skBOKZdC3cMa9R7BGDuLv8C+3gorUyRchpFTLorcj0IcA+DGwkkjBhR2RH9s5XpEGrwFtyMRP1ScpIoWXZiB0pvSJEerY8Rp8MOCl6QGoiJYI7HGgl77HrZ8w50gvHzWeIKdLuhXl4TkEcxGpqI5qoB5JLp6BUKCU6EbqezprglteM3XOzyxCyPUzTjkKNbOHrbE1o3gQtlKqPdp+NY7nVyt+EqCqsCUFhObMwMHKvcUhzLqRoDf0ETYdZ+hMLAXRTcCH5zaAVP7ID+oDsSKYcIb76AUOv8xTFU9UbQ4bdGTZU6ySDLRAeNM9iv7KyW7e+XGBrniuvCUUWnqEr3fLr+ZChSILESJF1Aa6Q6QQ8grxa+2+OTWP3/HT0d0A/KJjZw5ED8aneLONFyZ75VdWIP1eRDySALHkkmLUgDLByMUTnzU1+5HXWvybPo+b1zxALlxgZPnY0+hhNCCQpNujaPKSaHgPkPJj3lbjyM+auJqT3A+4d2tDgM4XZAq3/QznOvlG0QVGi6iT34ECX2jWC8PyDJ3bdgH1S2tLa0T2vrlfE/H5rI0ddBtd20q0GxjroJCOq6I10Jx6rUD3+aWE/IxnJn8RKlpaQ2n4Wr9qd25JCgQ/PcyqqqDefLv7OlTqQN+iTUjsVCVtMdCia4e09zZx7DkrTeIUHCYlJg6E+X+YBQu3FYm5SPncY7OIKYFWFKuY9VbjPQD3xPHExTvbOOm/oVCCVOhWOnf71zNBNadfpoPxB0USUmQdcVxobL7pyDy+M0S3GnEDi+HjfLZnryP0rSCs7n14M/MMoPijCepg4489JIWHByFJkmy+qM2u8wLhaTDP5iXbOzdQz6730aUVwq71YaacKRAhkTOwzS3Q2HqzaUz2WSYZEA4Y1cV4TzsqfG7daExU1Y3GRKm9x4DN2aAYFA4pu/dOqmbYpi8IwcSSbaYUV4Ja0Cp3qF+jqFj6i9OvtyUzDwXdMF3nvZekGZdHlfLrSSmVaKuHX25CZ0XB6Qf6VilGzewyswWbz16gNVNPCGMqjz97kFwqgnTo0fzr90z0KUaplfgiD9n8EZM5d9gxBBncMahEeOgLCbCQgrlRRN/yZy4lpEsnyRL/YoSwyaa2ZAjMQkp+y4OyCjQGlhwUh3AMKFnjcvI+Ir2m6KZlb1RggKBoer9I6ejIeFRQCho+LYGWHbiLusTlVmQ5+YAYkcaJzmhgW43phhDgQmt7lAvjOSz4myX4Hjpr70gbIS+KY8RYFOI2QPiKSGO3ICQDMnwrwcIhvI69pMAb+xA1X+XResbP0kw2KkuhPlPeNMG06RZUxUVNl5omzqVbPonWgSTUWWz54D9IpbuPgwJlMdQHs8CM+3Uw1lYucw/W4CRF1Cz3EmrPb4OmomnCWx2i230NZMJ2oZTSYwX6HzAnvrT9oOzkMBEAxX74POz7c/uRnmjsy8pyFeURxgfOQiPZXQiY/mmZUrKZ2fsaLHzvNzzsZEAFABYN8i3gd6T8xWw7thv1iIq9weDSxabO29Yhonv7Gka3T9V8NhcE95mMKRCdMlPO+4zjyLxVZYuPHZE8C7A0Ceymy5P8g+bhIRAJexVKgOjoEinqVqVbfDrm0qY2h31izS2npzwRS+irryjpjyYjUH3INGpRuuc88oufEYkJ6uj7DwB+aNBbT/dUVlfnU/L5ZbEre5C+uJkzHj4zQZ+nxKDFSEVw2IgGBrRsw1nYBKeStXLGWppVjBPKL+faNJDK75zcu5yI2MIwggiMn9w4EigyTb39UFAp4Ojih7ebkDYHfGMx6MJF3/5dzBMhidtKM+LlXkMvGhFXiL6Shq2Q/kykoZnsmXD2p076VMdm3ekjoTvdYNilxTbD8y7YCi8ckJrNpdGz7+njCZfvwdhXKG83TT/wg/O4qhsxCLslB6Ifiphmg4OWIxC4t7FZCCWWWLH/dujaP4vZ4apnMlU67y5u+gSjBK7G4DBWbMM4oCZiNrkzpdQdqiBuxLM0nWA+DEcWRlZ6NIbymIOktOM1i4hyv3dQmF7Uh4FKJ6/0EhXIJCw32YlsaMNQl/41gkX9lPcJ0l55J5l0/QkO3cs3/A6hFFjC34A/sLS/7qUk2xlV1ja15ttNv4XdZnqv7nq/9Xlhwdxt18tvKlIzlJ4+aRihlNsugU3Xw/aauQcR2jH0dHP16ndTfeVEGJJrkz0ilmgK5loLgGfWf7SwYSqWQBCyBUcCMohfB+4iIIa46ho0NE5bmwd6eYRz6jY9ncKAuwR6GVfLkfajh5fXhXSxyodU0NixP0uS6YVzE8DWRip0PBkXkIqESl5qqRHq/sDFBd+93cOee/qVK+8ocswhU0KHXlbs3nETCWh1RTOcU+ccHW1+MOYP0jMLYfQbqPTuJT0gLNeYdsXAIBCYxoap8cVv8jY3Kk6HWuhsDSkDOeec93pK5zPXut+b4MqMDgqTRqodc6H5VE6zDNyt0021KrHh59p37U0VgszWzZhYqjNboLNpD0nGfCPUyq+1opuyclOxnmnAyPq2Aa+HfMWBAjIQnm0l5yODw/16HZqf0Ye0muGB/YrOwLS1E14sEjPX1Z5xtCvLod41lqqAlDHt7DPCZmAkOH3wxhvo2Lnm0WL7ZD3blGx3uqV5dFwzEAQo9kteRSelzHzxw/TVgDOwCG4RX6zmNjViMa6tG//9ZDqw/a9W683Kvb1jwlzpGHsulVXP4ywiGO1NY5p0IACbWMKKb9LXfs/03abvS4hhrcIRIl9uSbmrS4h8anaBf0VC95rVL2IiEbE6k6ouGxNRQ8dkKtPy8DhgUO3gvW0SMsqKgqFdCZMMuw/3GMkZ2/CJIcZH1BXA+BHjevuJUh8tG50qmu6VmL2qU2NRskXTxPR9UntyIGM0JcrJ0qB6RyxNWb8xebMbFK4Fr75F5Dac9AMAgcnytEfoTc8EwUOIn6qN/fnPBUXBT64zdKMY7Fz/nzF+dhr5BVPkbFbmJ1H54nIjXnKAy82B+1UVyaphsV94/H/glOQ3aCVi9QNAmCVk883bL80CUgDQ4S52UZM9Pqqb1Tne/H8I5D119I6SJKgWTficQcnZEdzkQCRXZi0N3ahpP1efgwuMmOwaOGK5zTQ1RUlqqpMXOtJR7pBxfhJOTsnIEbyb3Ccileq8V4TijuGCObJOY1ol3vH3GPAQfMjQlBopDFyEGBpP81WGF+Do22uPQjRC3PGr4xRXjiR7cX2ughoCxfKaE8SUwzhu5bPWUfjslVWbRzb/EVrA/WUh+/JI/9tCYs4f6IXlp2CA3Fy4/rCKnzC97WephwsZs39fd2clYq+0JcqdYT1XRHRulSERuM0Aa8hpjEbkwyLfD7pldtH9W66vbALxmEolpKXjAq0XIEgui8UPhgBOQK4S9dp68G3+GShH/5+CshWqMm6WuD3lR/EMOfosAdKFZD6OMItE3uuew8qlGOJHYclYqEdbXZedVp2c2+XSh8ttqKrHG9PlPW7aHYKIm3ljMBgehW32PFu4lyJTgqnIoG8zUdGepzcEpaxbdFaWCH7a/zWubdnVW5CZlJHBmP49CMIbRXclKlSwPA1gCi2bZs3LBAK5sFyefuVqKP95AoFuRfN6D7gloGNan+a7uc8zqzjSZYjZ5g51VwLxTx7U/+NG5d1fOYjbyHshcMDa/sX53gSHzcmujfgqA6k3axU4I0oSv5GHPiKScnLE8b19SOjKf9qtOwvmPZx1f5kqNxPxYyvCjSbp49RjmGK9Aw5YUjpDQRg4SRnamexZaXnFEjG/qNNsOvs4EkWGOntupoi+R/0dK3gTdlhfPz9itzlGukV2hRFREwmnY+P6QDDBh9YZECdZNS0FFcFll7vGfGEsZK9mi/DLVN/Ju8A5bz3buOMm3uEbTk8oXsKmtuj1Wdvgz67o6k5YTP+zyOI1EQ12tf3XN0bvZRt0x4yENTqabn0VCm9W3RdvdmUUow7BzMV3q+1B3KL3nBx4dSuPo6QFRReRHgaBz/6/Gofb9qyJ/XMbOHgBcX6btcwga9OPRAuf3BDOX5jSyr21bgm1d6Ol88bwAQpHF9CT3AmPQK9ki/jSc4R1DWhVMuEEMUs5xWpA6Mb+nW6jisjiIrYHRWl4482dGHZTQ7R5ra2buW5pdJypPe08HIOoSnCIUIWYTu8W/s+jvzlbweBQMI+auYmgbrNMJF7EkWgnYlkrwQ13qGbj/ndJ/sb5OowanoEDYphvhFwfCG6uB5siJLyeH60geHQf5bPdnbDy1C8vbNxKs97Y4fV8criLSb5EoMmYafIM7fjj/GLoIzF5fq+djswPdhdprUsO4y6knGdi3NNaivb2D24pvFYzQQ9lb7yxCo9EE0D/EGRjqR0uUCpXivIleM8PlOr9cYAiPGSigILLibODpFW1Fen4gtPgaVAgw8QdmxXwgziu8fxkrmxk9gYHkVjNZ0oQyYxFqkrppZDO44uWMekES7YDeRFBc5uup/4IW5umMffvVFXQigYVGDTYyivQUlSI3ddVRYOPccdhijnP7pjKbmpX0h3OORIysrcXRIJDU8KjnPxaoghrDAgaAmWQqrNV5Lq0oPNrsAlJyUapcmjnTJrht/hThwM94SX8fw=
*/