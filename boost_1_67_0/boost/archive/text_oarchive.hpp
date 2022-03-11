#ifndef BOOST_ARCHIVE_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <cstddef> // std::size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_text_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_oarchive_impl :
     /* protected ? */ public basic_text_oprimitive<std::ostream>,
     public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_text_oarchive<Archive>;
    friend class save_access;
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::ostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_ARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_DECL
    text_oarchive_impl(std::ostream & os, unsigned int flags);
    // don't import inline definitions! leave this as a reminder.
    //BOOST_ARCHIVE_DECL
    ~text_oarchive_impl(){};
public:
    BOOST_ARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);
};

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_oarchive :
    public text_oarchive_impl<text_oarchive>
{
public:
    text_oarchive(std::ostream & os_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_oarchive_impl<text_oarchive>(os_, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

/* text_oarchive.hpp
QAWkmYNtZHAk6wFW72TcAITWGZbbdpIqb6UrRoVv/5l/tt70LiaKUalVb59HGDYJ6aYkh64ItwmTDXH2S+MdEzpnIQ0f9ji2CKO9mQgiGmG6gr6A6S1RnYi/zVFIe6HRc7wooEreabHrd6Ny3sUpPMKhVJV08FpWuXdzWDspLw9SZQns2AJWNkea9eksB9GjT7VE8fp+7ISOJxiTkkUjxBKwobAqkyj5xithc7fQ+TpYY46u8uw2KdkoXigTuzozaU2EINFduRjV0+KGz7Yrf8mpdo5cws+I/zNFg1Ok7vGeulntahYvTJNkETtLs6oZBLdY1fmtmeFJ7E//sM7dvE8M4dbW8SctKPb13yh8VF7Eh8kXBRskJcxWEYBYkM07uB4CQPzoK3kSPOmgjmgTsznBURrNTHeKHG0XL2/KWGSOQw8kQ4G3tjOlFl0/K+1hXvB7BUepadMIfUie+fp1/Jr9XdOrSd9N6OQqkp271g2fi99oFNIpMVCIIhAcCWAYHeoH3OcMy9t799uXT8Fo5QkB4DNt94HKbPIBpFCUJTzXv3vEZ2JjtZXn37HUXdqAZfYh34jTYute0o0rm0u3/p3x2qRjf3BSZ2WhEJQBJCDkSCz7xrd3/zQDRdzH+boTy12104c34lIi2TPiiFeGfu2GkLR47uqNGHcl4LlmYV1r1Ap9RRDqVEySnayBQrwyG5g9AeFal+S7t28zZaf+8kFkd71aBlO599F7ZePiBzI9uhcjJ/MzZqR2EsIetJeO//hdgrwpEczDSPc1xClYk7teX193JH+EhiZ5DDEQKokKi0iDAwEVsDj7Rq9z9LoRP9/i6wBD7175wcWgU5449IBa6gg0mYVwICiZ3ZinAV5UsPe2kxPJtre0tBSzdNgPmRwOvYCEhNyH3MDExLwLPLU0F2BC6LFQ2yIXM4Gj/tLEn1NPI7tchVGHUVVVHbapqZGFUaDHbkz2CGXqj0UZvM7y9u+gwx3gGjTBs1Fb3Q//5SXafyPgYc/xNa1ADt1UODhgtU7h32dgEfwqONHBxBBywiwiegACTi2zfnwMy02ELIaJ0BiXVBenVPbLz9fbJwveR2pU6/fn5uJS0v5mY2IKejYWdEvv4+E9icgANOuQKYd9FvNIY5E/CSU2qRweBkouSEwOs8J5CiJCrBF+UEY/V0YTCAICB7dHhgvEfnTHnFF+6kZ9BocbcAxDN+EMXj/UwA4kHzav/NkxXlZQa98EWhANY9eDqe8vKytvb+bk5oZmx6YMMDp17yGIhCDR2YJ8EbTPWySCRZzAB7IqtJz35IN902KNus+r7KWXWpAFnzkKunU/6EAZivhvBrawoDCzpLQIiWpiKvJuBAw6KFSz8oCyy0N+elU3QfjaZrb6EvCx2UfHHe4JMByrwSE9cGUbIO731qPx8OXFjcmZhsGcn2X+u3gLrwBfxRHoVVgeCMvZ8vr0YC0XncAACoMoL7nPpiFOcVkIrRyk7P7eEaNAol5dHAAaJAm5dOT9K7Ys2GtGKbYtU/uf/n9W3pKly5zc5lcK+XQredBUzixY5Ty5LvvHBw8PThHjF66gbRpH9+R5sns/tvNa3DHUeswQBilIlPsTBiXneyI8HqeM7xJBUmMEFkOlKb21m3JMI0APfnaAFQM/ecqpdqrD8mka2nbebJlEfI8cZdlut/JZ+kHU+/57mO62wiq0VNLS0vIS38tdlpR+Bnr+BU7UB2R8IPuOgyRO8YFE8B5PzIFfpMDv1VDQkojelGDKkc9f7lvNxviF8wGZu/xHzyfQPpu3VIJg152YsrRUv99WU1M0Am/ehDFN3346gWPki/3f9IgCYNQe5KJNAi9aiToYwYNoVg2SI0SUAxhDgBbrJy0WGhKDhnOdXi2QoF6K6NStP+XPyf5oJ2pZAwTWd8aFEwCCgXoConTMGz0nVA/pS6S9qF8DKE5o1wnv2OQCOWu14Ag0Xp0xS0ainA34A1U+Cdkkhwsso8NA/VIKiQYIBh3WswRVDIevdgOhrubaF30/BcluSZIdg/QAZ3R6du6uMvnvd0Nm9kNnD0/CgmWvO0yIsfdIKERUn659N+I5x5QP4AMNgZtMCNx0aVQwuVNFZ1CkASEcOu6BA/NTMz9BTGty9wsgkDVwGFcdN8+XYggU3JvkvsDf+4OS9yMlKz4+C/7gvtb5gG4Z0pa1DOuyz0+mfIFKu+Mp9NgXtGz7oBp8ebOwhp2Gp0E0KUiW8jH4rKAAcohMR/kI/oGBYroKkjlCGonwydzO3XrqL5EG79C8A71d9C0nHlpRH1PueryTvQomKsA75tZf3nnDnVH8ISrtwG7QzbTJHtt0aimjaKYxtT0kBA5dyyjlpKJQlHznErf432rc0ig1snT9TbNeWP9UrO8TktPkjrZRWel1A6NLLcHyF3x8V1LgXbsBn4oLrsMlb+UvC5Q4ODZGTsWFBET5sGdWqSpNxjXYa/HZNPOePvcMgEzTyR5va2zpDYAe1jkPRfUwZhS4fmJjxIYtIjpsUg3OI0fBG6rgJCxS1agfFPCQ1ay72gT58JcQrGNlu8rXVP2TdDfQlixPzzIly928KGYbLlVOaTSYEJYQSzpDYaO1MFvCisuVSeANorEkRwuZKBWJY9ZARVExg9i4eNworICeYDm8Qp0WypY0aQsJbjQ7demkAwflX9pgNVu8BUj7tPUoLinzZZuDztTgMcT76WG/94S+QZ5BBu8JN2r17V8H5E2TX9Zq+45PwAWFVXgbYlAKqafaJ627WCMqVOsx6/fKzQjVNpRkCbUa3D5VQYICIpO4GpVydJY0l3QjhgrucNrbJqGE5Bqc7zN4pO85fLXN6y2gP0jVspo2frie/1NiCUwgq/xtA6gGWsY1cL4TnqDnN54vk+cnP6FYb7OQrk/22ngKwNMbeigfe+lqXLJ20XueYDZjw3dM4LiB/8GtiI0bpjELERoKlOyTiG941zGxx+nXLxydenGRv7iqSM61N/gQHeIphAMKasJIPX/HBaPLXdC487b1zn2LXSrS+80KfHReHTBE6gSg8M4fkJmwa0NNaAeGA34voe1btWgsgHZfb6NO7L5waXLYb7YFSYI0e/S7chM68TmKBBggsXE0K9yEr41l0NgHwLIsuVZgYoVdm/sOPQmMch3sY5nNt0kOqfTKzFERBIUBxQZa43oh92harGwqv2uHBRIBZ8vHF28NAJpiymXcXtgwKFKePBmLGmRobeU/sndNQBC5pCqIKDM4eC/WPkiIfAs+cLS4z+jwAypv9DDI8CUPhDH9NFwXI1GyfZw178ycwNVh3HICtn9bX7HYcmoxJ6Z/pDjdNFLfVOl7AyMtNbK08YetAOOkVJNwILzUSKvS9G2fhbamcctby6QsMIxpXSUTLAMTV0Kyqv3cA6/Tqq4dHycLg9FkQ4i2doOH+68kYWZZIhiUpAvnPCxOqmMuSrajuXmV7T1E7Jy5NTnUcnL0PKKHPkuTJe9GNFRfbtBZJUTn5n2gYa6f5ySqzlj+xyZMoDz5kPwLyQ6aDRsikF+qd3POboEitwNxYp8yy1Er0TJJNYvrHhgPN3Lj/sAUelIEhjJk/MyIcLnwn518/c0KfZHBOg45mhoLgwlc15v1Ks9prEV2BhM2Kx/n2Ca3lCy4vwj0fxoQb9/xbMjAQCXw/y37NsYhKznRUDFDZJfEhjBrSFXbDNrW7t9ECvbbsCwxqqaTY5E9JUVsWhV84faxpsTwImzBjvGmC982w/xnjvtfGTOnLl5cOc+lGifDqv/6F9zFF1xr0uX3Xod7IPD5/NKugLUf+b3mf8lNEZkRakC1Co4WzZpB7Zjbvm49DTG67/8Seu7aqfdL6AcYt3/znlQMYjhRygJCA8OAgGZ4W/OEpBggwOVwZc/nyhm9is8ZfJ3qlJY3C4xMazfdM4WKNUs831moNny8As25NkQtva94nDXiw+PykXULyRsKks0FOcw5JmBFBt61X5z0SleKss6EyZkG4h5YpNoPz0QvyQI47HOFnkdHFfArlfXKVIhW62CCAfAW6yJ5V/0aa9gE33TrpfbNVA18PCgsrYq1PY47GKiiNFclgCfbECWbLiAzd5XVyR/BORx5trMXkvJO2V8ZYrcCUjSKLiogT01qjmTI7rcote/zVQPZYAr6HcJd0+y4b+XRrcU/kVG2H/q+/GzsrU5usvXkBadC/IeNPXZQ1T6IAgwTv+B4MNBypzB6OoOxUgC35EwVEAiC9/f1TTUIwK1odVOcfGiB/UYauEw7jZMXYTtRlBfMhw3AQUqpZ5tZqCRboqS0w2gUtSCaQmjV0+7z0yFsP8Fhxe/jSMUARWRfGAaEQIFeggB10HtZqEHMdHDEXahbqBflkpqsGcEHKHwg69m+D/HHTa6ncj7GnXyLI178rm5ew2USc0a4VMaVYFDAJQ+6ZQkTtO/+gdZL869E9vHIKguQqKlBbd63kA3FhZaiuHvcwKgXuF9LIC7EvoFvD0TuPtc5wa7Hw7JkriwtPTVOL9DZC7NXIa/2ZbV45Udv2nano6WkQe0rQJPpu/4MvZGKvZOVYKynCVis1HoZEjpiIvESumREdFazlwENGHRrDGzoWyTzTGI7myVXxtyz1iLgSrlQ3+8bvSGcfPErp72S4k8nGbHtGPz4vhgExegRgdDl7/AvQYvZF0Ig18xgaH3MRV5hvjTcKBc1EYjOc4gfXumiDfu78b0KcsTroXOvDwo5plUe8BaEScnTZdOoJ8Uq2QknTkBeXs+DokRf6St1PEsGHiwGXPEluwPCji9pbhv5Bo1eJ1I9NKsfhemp9O30aXrwO/Iac0WsOmbfe94PvhByQJweLixBYsUpkaXXi3yjYcVJROQhsEtpTWW2SI2eG8dbCgvxckij4KY9ih+18QL8V5+YR5Bb+s85ENvs65X0kQ4F6vpvjDdb1lioHSMnOiIYD48dVCTzX2rPgouiehcQAADBYSuUGhfWHl3Y6MlzoEHCXCFZngSQZiIUTc1i7Jwp1eejWCHz4qAd2JPczkjmVegt7baE7ZFZzNWQfeTGnL7n+N0xyNwoeS5u12rA0u19TCKC2u4XvV5e4tk39yOQm9n4mORlq9G2Vc35Owpu2onUAWBWOYhzjFvMd7IYdAGSuJoMZM595PkQFHphNhJrGx4sfqw8YayUJd/kLsdY9cZwb7mqCFTQS613V/zXwm9M3X5quRpi+KDKvZq0yMktMmJ0NygE82Pw0F+Jfxx58s2kz8KmUUZvmdr2nrHvpgEvhpNf0dlVZ3xpbQpnkrS2mqfDwIQq0swIROvub3cxD+yWUWhLcQ/sdy9MV/Ft8Ojrz3N0cJFdA9MmsM5TD65YWxmhX/CaoTpWGCdJBSuYr9X2iQOyYR2HKDMQSIOq2zsEWVt2TmFWKRKb5qzoioc+c6969cKbsZ5FvrTtqIXM8HVsY29jIsijjNTNhiI3bvlP6PkqMeTm2hjn/R6cTuu7dsigdzbJNnraC/VdW7LK10b18iws7REI1fGqc7rL42dBN1VGYR4ukqVhHQY+Olp8RgVABbLVKJ7WmXnv7tog3JYlhe/tzcse9T/O0ZM2eKYy/Ih4B21CtsjufNCPolSdZ5rTY6wleIh6gUIW4Z04yIqioDMbsv56AsYOjaY3NsuVMfPbEALCs0sNMxhxRqVRuTkmRf9t0w4kUG6fbQ6eho0VWjbKWDjXFxUuafTYZ6Htrt0BGqLHC7gHi03nUJXRNTFy4X+j4JTcJhb0N0rl6djEmMsriIV47WE/l9CAk/UA0F/QOswSR4v/BRIg49BlIVOPyJrr2ponj8h8LtQ/KtNAbi3KUfGZEGKm4vjmtCiTQGxVZMx8DcMj4WxPyVPJnzJrrIw6DQK+VAT3ZkvdXnseLBdOqhKXLSKNv1+NduzB21RLebskmTaDYzmc7iMxPiI5lb3cum0VbnPIVP7DbISaxWa+LkXax2iQM9KjSsZ9z7eir0aSaqy0MeDcGfmxCugeO+LnIxauAqdPIv3P8BrQk2zgH+AtXhzYlCbjpYq6Yz65gMSYVLwwbDLaf6d4rw/GXL8DH6h58+zBjMMtutXvJ/+aX83BD/LLER1ktEi/BV3Q+GJD/PbCyvHtG12RTb0UCnLMhMucEwOPLa4fsnxLwm1Ad7ZkP02pdh14JNuHalPhUOA9UUqZVoGT9OkTgg4SGHrFosOZY72ub5x+U+jq1n5AA5cl7wKj3PAgSOACAWnsUsSGSihXpSSbVG1LS1UPn8tYHSPON4WHJu9ry8u55NufoHK58EuJTnjZ5tf+mgFbR7sNwS4I1PG3/OenryLDcfprON3PfAakH+hmlRfyhzfe/cfuM9gIp1K/rh7TVsfzh8ZjouS73gUeIUMOtNC/2tgaGqaGINbPiRnJkkvzuJpvVdx39oz3N7G/3vXu06FP76MexwvKI50JBXU837a4xEKHF4AKeOSQAdVK0lJ6YfJtfg43tG5erKbJXdx3l/4bkPLKJ6vXXo7zp158RFy3V+3Wn4MTAuTDj3gfgfnrOj+se32PgB4CYtETYtrHYN2tGZMoQNRg17akPG1yvvTAhV9VpA3G5aL3WftcVcngrMi4hZVPDH+05gXts017I0HnISW9tECexMkKEbmq7agP6YE5DO/t3L8EBSAqrAzgA6JdArccF0DhsjGsLb7w+z3jZb8n4zYTw96K6Rkv4SH443x5d2iPJDp82Cdx2Hp/n27gYbtHxpTAcLUqn9srP66Ij8W4P7oBe1h2yE5ed7MffUAMzPEYNYNc//w+LOK6YUYu6Mbe2E4Q6XWwQze1GlwTktBRquLIzXC0qVmrXngbN7ZRGqIn2cVYtDpIacgeRDZURvacuC3sdJgNeoYJtvA0/dHzw4JTh/xYVnKEujYFXAmucQk9fEwCekcW3aO7mj3zbn7y5Rh15C4YYEn4KmI0t1L3xhszMksZtULQVlg+yTGDTwhnjk8cw3iq02Jz9J0b1cegPg9vk4QIsj0WesAYwuUZ2fBsh3xBkrUs5qTvBeXVsd7jqClX3sYcCgpvm9u1gT12PbLTR6r6EDjMSv2bRQfBvMOsw7GqlpIWyV25JDSB247XJwLTvk++rKG52/Q14qpQTXvAPeg4uCQgIMXRLRBhrKK/OTOvcaHQ5dvE1ziELTEA31JON7s/OKiHibiUrelAai231+llutUEdPBlRorZaz25v0+QRVffKSz3xcb/hDzCeG9XGna7KCsilxkK1/Q8x5RRfF6sIMFBODA4fZoT51fj8FWJ9O4rGeD7k8IFN4YSUy/MEsklg3frKKeJ2zu6ywMUI2QdXYqaxAxQll88tOIKUcru+7Lv4lXxDsrVTgDTtHxGqRKdjaWdMwgdCKlSqdaKT8BpxFl+mPftp+ZUmXJrach5l3BPkEWLX+nyzso2/9zjLCjtJlLKoK0S15Shmt3QMvYbiVDu2jz0ve+VoLig3V6wJAXdaIoZpUWniVXEZZ/Ape/ngELwlrdFSd22jorAv0R/so31v1ioQ6YzrdR1/mVgPIcqSmCzBOQIu1KR/X6BGorPxJ7C9CbHYmMwQ2s6MPU0zrxRBTHCux7v4wv4f6C3+Xgg/9L4Mi1NDZmR8Yu/r9w7O1EvA2SOI2BZzNjhGARXC20FzLihpkJURhh4NIsLwq3GAe28fVEItE7VSAr2L+6hnrsgOTs/1sn3O9rbO1ES+aTyAY0bsq753tOPmyNSopS3z59f2Q6Xr61rFHfRViCQklT9C9IoYPy23vlHET2fBSglAJE83rMwLiErQZqvbROnNeRYe+99bELIlDVpUMYFJbMZlYAiFzd7NNIvKK6wX0BmXKWGedXl1ro4UAQEPfnks+fay2XeoaPzYcRqao/1zSFujasrfpju/d/a+62WzWFC13FdaFKHnNh5avN/PbX9sjCTLy333+Ba+lfB28ajzNrxcO6TYEf2eyCFUm1J03VLoK8CxKuirjbMJAk4MyWEd8IGpX+akfRAy0C3YppPZ4k5CKCpwBnvqii8g4Mjwu2/s2AXZhpbZEPzn3UGggSXUgtXlH3+q6I6xJ/f++GCGVBIKtzXx39rigFR7W4AfkM1Tk0RQbIA7MhOd9jjBMEfuT/FsjdH5TjXd0de+fWzNDKns2T7VjzA8Q893fgCJMJiMtM4rYA7mDULO1yPpSr/PuFgEPVdbyk5bOpcMzFWad8mz3lZ6PcydqsGYWGNEZpqxD5SlND3vx8Agh8NoiSvqeuXhgFCA1BjMjThv2bG8gK6vgCOQkM4NCd4ImQ3SNfZ04XlS+rv3weBaIFd8P1HxZgJnWHMNP/jTMCfm71XiISIzLpz+QrKKXT+uZFEorxa5XA0/vvtRTCpLRi9Ph3xGyMDLla+YxXursNAyqYRQSSBNcO78wLJIyb+uFw34ZxXQFpoQaL2a8a/o4ngyjTO1gdv56R/6jGkaKqnD9Z+EbZVQ4Wnpsgq8K5OWtVXrfzSSl8etbX4VpAJjXgXCWYV2ygTIpYcFuNCqu5t/TX78UGLeo9GorM4McTVpgnmx5/F/IgOD5u5iJFM8Fk+7ECxnRVM73OGfrZLULV9+oAAaSw9ntZy9gH4q3e/C15EMU54PYEGoRSERNC+zSL+aRuVc4AFDYqR1MtoVXLy3ovVK1iONFhq5mbVD6KKa8gHfTrFj0935d6k2N+Z5y+5nEeVh2dH5zTU2O76/a629s3sXkzeqI9/Cjr8KFChb7ttY02t7QUhJymHHKPJLNRF1FiapdVVR4s9lF2eKLdcthUivPXOEXnIVw05BSp5Rx1D+/M2N3ddm1WEopCDJIKB/POcmw3/1H2GSZXJosYp0RirlfAiD1oWSd1Fc6AhHNLvIkWiuP9JgkaQzt0xmLL1k4DR2BFg8Y9eaAO0ORy8XDAy9qkjPGbHBu6JDTBZkRov3VghO/Y9nwS1IDIm+mxhb7lOaXWogs6ooMSy/kEidWBhoIEYcPff04BPa57y7NM2yATLyDjyU6sXemw/kkwZMXz897JreiWix0XlxYWt90qR+fJW7uwTxpPvWZnJDrzwZh9y4KfwEoVS//VeYDEqItlC4+ytqyde2lL3jTjX8mKIOJJ9jFhem5bkIuLPQBDMV2D++HdIkvMHSC9GfVP1ZBoYn2ttoNzaLMqT1kxMdXt3mUX3fy7u2oy1+54=
*/