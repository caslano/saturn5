//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_SUFFIX_HPP
#define BOOST_BEAST_BUFFERS_SUFFIX_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/optional.hpp>
#include <cstdint>
#include <iterator>
#include <utility>

namespace boost {
namespace beast {

/** Adaptor to progressively trim the front of a <em>BufferSequence</em>.

    This adaptor wraps a buffer sequence to create a new sequence
    which may be incrementally consumed. Bytes consumed are removed
    from the front of the buffer. The underlying memory is not changed,
    instead the adaptor efficiently iterates through a subset of
    the buffers wrapped.

    The wrapped buffer is not modified, a copy is made instead.
    Ownership of the underlying memory is not transferred, the application
    is still responsible for managing its lifetime.

    @tparam BufferSequence The buffer sequence to wrap.

    @par Example

    This function writes the entire contents of a buffer sequence
    to the specified stream.

    @code
    template<class SyncWriteStream, class ConstBufferSequence>
    void send(SyncWriteStream& stream, ConstBufferSequence const& buffers)
    {
        buffers_suffix<ConstBufferSequence> bs{buffers};
        while(buffer_bytes(bs) > 0)
            bs.consume(stream.write_some(bs));
    }
    @endcode
*/
template<class BufferSequence>
class buffers_suffix
{
    using iter_type =
        buffers_iterator_type<BufferSequence>;

    BufferSequence bs_;
    iter_type begin_{};
    std::size_t skip_ = 0;

    template<class Deduced>
    buffers_suffix(Deduced&& other, std::size_t dist)
        : bs_(std::forward<Deduced>(other).bs_)
        , begin_(std::next(
            net::buffer_sequence_begin(bs_),
                dist))
        , skip_(other.skip_)
    {
    }

public:
    /** The type for each element in the list of buffers.

        If <em>BufferSequence</em> meets the requirements of
        <em>MutableBufferSequence</em>, then this type will be
        `net::mutable_buffer`, otherwise this type will be
        `net::const_buffer`.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<BufferSequence>;
#endif

#if BOOST_BEAST_DOXYGEN
    /// A bidirectional iterator type that may be used to read elements.
    using const_iterator = __implementation_defined__;

#else
    class const_iterator;

#endif

    /// Constructor
    buffers_suffix();

    /// Copy Constructor
    buffers_suffix(buffers_suffix const&);

    /** Constructor

        A copy of the buffer sequence is made. Ownership of the
        underlying memory is not transferred or copied.
    */
    explicit
    buffers_suffix(BufferSequence const& buffers);

    /** Constructor

        This constructs the buffer sequence in-place from
        a list of arguments.

        @param args Arguments forwarded to the buffers constructor.
    */
    template<class... Args>
    explicit
    buffers_suffix(boost::in_place_init_t, Args&&... args);

    /// Copy Assignment
    buffers_suffix& operator=(buffers_suffix const&);

    /// Get a bidirectional iterator to the first element.
    const_iterator
    begin() const;

    /// Get a bidirectional iterator to one past the last element.
    const_iterator
    end() const;

    /** Remove bytes from the beginning of the sequence.

        @param amount The number of bytes to remove. If this is
        larger than the number of bytes remaining, all the
        bytes remaining are removed.
    */
    void
    consume(std::size_t amount);
};

} // beast
} // boost

#include <boost/beast/core/impl/buffers_suffix.hpp>

#endif

/* buffers_suffix.hpp
jl+ZF8jj2gJ3k2AWX7adciN8FvA4pHrzQmNIyfN902XSxVaxr9NBIhQwMFQZyZOQlv8dzZ75HF4qTecmj9EtdXqsDXhMNYLEuREbnap5ujSeW/IiM0NZrHoCtvnfSQv0+83Wohb4HMac5ebVo0f5/KGAgrSRqkVHtneppdZSZfI7GiMd98OkSsaXXjEYyvXPlKrRv19Q+P/bC+CphZ445Ym3rOvr/Xq212JzTmWpNT8yz9Y9IVN7CPSwo0fPyaujM8rOP6bWSShYSgKj8N5WGMFzYEKD+OMXpt+1FFqf+75e3k+tn/l1/fNbO5WXpGtfVCR0DacM151+qFkGs5ZeP+8xK1NTTHwKmBEMi7k9HySJ8QjF5+04oy0YuBDYyNiOWbtOn4Tv+57t7pBLPsI2FcFliugn+m4xm16nQYRyEx6YsFoxrwlba8Ey90QtKkkZhfHcWZe1B1R+3W/1yAAtBHGoc50oVxiS/9Z7IFGdWHdFQ6HLkBnXQsjF+1xs8Qg2wv9iF7l93vAiZrXiQu8MRuK22RXAYhAybt4txt9YsUmVupVH5bOj2xyw+00a2Mp1BQR0JnOtfy/mHaH0NC5PqbPe5rDGF9Kja2YWoOlB+J6ABJ9fFflaTydNtO9jX8U5N/fTC5xAbfzEfoU4m5qR2IuqXnXYcBsRAD6G4e3yB8xQmn5BEwZmHTBnZfIqLIjENY8ULT4JLKaTycevnqd16mXAHMabESI8lgGlLJVakk0n4Akuv2Dv5U+uFREON1r5aCj6aqrFiAAkwjxqzTWMfq5MOMCD/7cOH6SFQ06wzYpnG42ez7ueulKI98EXgVS3mL1u4WONHzp2NM8mWSkZCFlJpxFI4Wf2ESeKinO0M7LYP6pN9M2BZNZVImm6PurUkj/er+9jmMGwjXlfy80KdfgV9Y3eEY0AWpz1a4lBETJ2cqQAysUSklkwVyS6vcxfiHunJlbkZViDQBd5lrj2vhOnObptUZoOu99QOoZWQ6eozxhASqT903pbI9AtvDHNeBKsD3lpW14uFFF1t+q0r4gBh3q9ffZmyz1Nj3lbDbZecfA+zvwgCP8Dr2ZWeFV890Z4NaNixekeDz0ydClF5JZdXKOzPj3FX7aPSk8PL23w+qJ5e6uo9Yalcw8hOJIAfccMtMXsCCa+IhXWpIGp8knNTQT1w8SS0hILaRIs/nNQFKA+KIyCCKfqzj/jx+RCc7WTWuhVGhsX+Pi0PzOe6y1wW4FonE/v8sqItt7sP+/V4Z/OsUcJI46ngSN0G6CcDwvoVWciQo02Hi7mTeNwUEy1M1SEaBosY1WHFmmwtupe3WNTe+7T2Bm8OdTwKcAuIBPnDQDmU7erSokAWy05k8VQBQiJEXZGxH7cC2AdNGUhcooIbHSMOwV431FkOa23WaXAHGzgzuvdJCoLUNMTh/WvaALCTmjKqHJ05Elt0aJFhn1NmCppLEzVPb2Kx+bDYrwMunCmxjG1E7az73Gm7lRvom8PDodA7AjOkd0jebTnGcPoB7134WKsVwlqf6AKe1oxwEmo6keG34Nw+f5CEBjWkuPArVaJ6htXjT2PjUUWPZO9DBvoOucr6miVW5CbE/HBcmKfJkqIzd6hGdHTHGuFo2Gay4v4FC6MxShW2uCxxLtzxY7aYMqO5TtmGGy4IRxb053t126YFE2s2MXlXzyb7eMJRYYFQem2eL1aQhj/JoeFkk81j7tFJWmrhUYV7EV3EIzHl7RSrdZ3BW9zbFn3MGjFuVQuKnNotRLx1lH2aSh8sV0fO/jr7RY40FT9HgyQYKyWlKg0JYEWW10gzzEoDWBRF9XmtTY8wGGwi2yDfiKRg5xQg0RAaU/jx7YmmOXosM58PF2bpp1DUHqB3Vt0fnWc/lPFckgi6EQ3Nxze/rCkOU8ZPhTeQU5/rNjE2uQyXjP7VwxFWrAAbaCpCr8DCZjVRA8Fm7X7s0iEMLEbhVkF0PcJ7L+yAyKOEn1y0A2/tNlsMmC7c503ZFJ6c2QyLHFuOD+sI39ONp87tVqv54vrqCLH3sNqifKvQpFPIjhmQVDQVFF9mf2BwAEU6HKmr2v8WLfDqQfhIW99PKIdWveLdGSalDW5QUqMRxGQ0JvYVCC8clcPKNIV8/hm2zZokTMeO3rYcwTpjEUns7jjb9gGxjLeElFs+xgbIin8kG1YNslu6GCSWwPEs9rrz/tAEZ7eIuYT+DOs240cRhBmFy92cqCY3TuPJzAyHoNs3BIPg1WdWpEGGmz6jniofDYXso4r63SLDx1e25BImFx+0p3Y6TAvG5725n4KdjnIX8rQWxyPfUsB9TzOWL5NVuvydy7JcvGTKKh0W68rccpDzduovH4TwxdMvK5hqRkc3z9IFDVpx3HR+tzIv9xcPVTFMOZJT3l2PEae2B/uewiP5VuSX/hyfjDi/7gu0Uy5k1e9j+ZslOoKofliWb2muDApvFjl8ANEd4CJSJH1t1ga6xu8msHWx/3XkND6/XcxRyPLIyqTbUk/X02p9sADxmLSk7F10XdcQ8LOW44YnfGUPxwU3LemkKX7sZOHQcF9aAdoLEwTqaTLszxbC/0puMfD7Jm2FNQ7ggyuUyRGpyGqE5JAneW4wRftpeWsseRDR11nGt0km63O27NmryQr+R99vBBh9rV0N8zSTdMEEXSSz+b4Qk6df34hMQAILPfTj28AWJRb351FEZlV1JRdRApu9tCH9c+aiqWKfMZTbgjDnjvoP+5VDxYRiFOuCq0oN3vR7TD4KJzUz2KI1osz9+aoNwhIUGJLpGRrmv5ATTIVvzxVK7FNsxgsS1U++6kxRjdV0zHYWlYPWfB3JhZbMR6OvY503OK7qfsMG75N1p3GaK8B/gY1hC9SXUO2K8JeiGYIybj/hBN+e+/Vz/YV0YGItgGsl1Z2jl1ONfO3V1ImO6rP6xiX0WC7c0YV0rzFsqVcNVlVH/4F1Mr0vVp4SjEgKlZ3nnNu7iq78Kc5+jEFSH0TnMMYB2+3q9hgJxWMHCZJMzls15zq/ks1X/ZOYiy/aWMor8Fof2Sa9dKGreM8prSI/laIXP2XV/7T5qX1PJzG9MXQ+1Xjb36oHCgass8KCEciVbtSoSHohS/o1Ak44t58DUJojzNicHgXojQ+H+2nYokHCCXLKJbLXNBYWBJxwhJxTQvpYI+G2ng4Hy3Tx/iMOWumrItyeWUJxIrwe4rGmqz2US9tKuVWw/Ajp//lhEDQG+OsUQu9Bm5H7xOQv5zmeF62Fl9vZ23IJ9drrsm6g6YbMtoM03yMcqc6vBihcdydFLcOQ9oRL6zw3A0/HpaJ50zm7EfQrTNrzldsJwv7PfhTH4zCRPdtcPBJmOzypbKYFYJqBCdvmd2DQ3A7n8mHTwx4DLyKa8bTXMYEsOY3OeZt1mckW3XGF+ImXcR1+kCVy69yb7F7yRDwwFzulzfg4cHcpQz/4O+4VzehCzRIGdheXEqeLt31igF52shbNDhr4+JXM7vmqhSWzSXmP+8juB8kbn3kTd0Z/E6tNuNOGcS442NAojO7YjTI1n2qPtg5K8nXZGVkVKxTBHaR9H4IdMyBxhnj7yRGTvi2HfbfRgIGT1UmODf0zw5bxdIyjR9cM7qRid3WUg6JjbzU8a2oOhcw3ZcO91n6k3Jc5MQoPwv+z8Ze0hqEl9W2nDUD3xRD9dK0a9d9ISPha27NaovmwDOXRgnjrHsibpw/7WRS52lRRhNYELbSiKXx4UsoiDtHw7msmPiljRrUIfcmU3d4Wpv5cugeXhVxO8e5yX1XqukicsAYHwz0/PhyP3V1j2Nc49CXnk7hcN/S/ziwRN2zPRJz3f/OBZGK9TLJsV7xHcN49ezBk0yrGhaG6g5FHGMR/5DxN2NExCFsjPGyrKbBKje33Se3++h8lE2EGz7BzH9NUsGPZw5Ntl35fstzBhLoJJxqW2R+WrJ/I61LEdLRFibIN+36keYlb7Cib72CrEXaZPJDDy9Ef6T4R5suW/JoV0XbhNAyOrf7pg9ttqmz1tt3ckVxXNR05R0KZNBBiyeMOivR+PFCC2oBq0l0ElAa8EjkPhUNRbhEUfhRVQ7oTOU15DPvhD2d48QO9u2yty7YHZxpWGFXQbc1dM63rhnNyNOplGs7Rxm2W/KyTbZWahw5S4R7qnCx+KVyxEGGSPEhRKz+bf5cmx6gSjFEEt6nkazD8f2IqizstcoIY8LL5GG7g2a6OBdN2WbjrG4ZvoPK/bMj1mrYWFM+kHrhYzj9eleeluHdtXwWHERQRJFapsF7+RLqeIOM7HqniV6uGlocGeJ6OewfQ7Ewckr5nV1YRVktT7Uiil+hOTa36Unjqdw+dHLjVmtRE5uJpRmusS9Wmg1hTDFER1NZmrCo67XUj/SaplFTd/6ayPzPO0uverCC6T+/QsKN3CKQkEvwlX41r9u0k+pRZTz2eMpN+T5Ypp1dX/xgfM8k5s7WYrxwSOP2KMlortIZvwWDzRQC33RZt15/naz7BS9YY8nbhIxSqAvRaAkhTvVuyXJSowv+Rwi8P7aYfiJvULrfhfEwFJ8kUo5A/FeRDMPYJjXj6eYR4x6uu9oQb9U2aDe2sYTeXSuRR3a8evORl18nQzeSFj7lhgXIG7FqkmG99jrznkfEJVVruyrvMahyav1lugWNCr+TeGpR8nn5zIxMuBfVAIulqtc2L8PTWKQOq3HMRv9wf8bt7YrZpSKVxZ35/1xActt+Kd5+uG6tflxdVixDNJZQnTDujktQtLJ1l/P1TipYk/XTerrJutIQKdboLTkPiURJSn8WH24csIqtY2JSC46AexrNc5kawpWfakpagRbSn4eYna7KZVS+vxHC7Z41bCxFKIBXasx2ITpkMxbbnFDeXy1DdEZK7OIXsbOixIpLzMzMOG/W32RppcV5932s/hqz2k3EEgahyxpACi5q0CdJjq1YqvJYaZ4shqKarCiK6gs9Ao6yfMy3KrrUBx8XChxnpyD9BURpiI54ASWX9rtS3N7PJasV/TY5Lh8T1iAkXJo01LyLcm/edJF8p5eUAQvrBcsS8P3Ml3avHjskAkdFqA6grv/MM40LzRthI5vVj2656nq7NE831ufZPHT0P9PBvmkkK3NbGN2/nUK4GBbh/wjJJxDpMPDYtDtQLI68Uz0kNMqu80BEnIMzdHSzmuFI+6eODv+Jn2X6EdVFfEcVKcAfTGqxJ+JXCmgwXyTOnHXSPYTE+b+jIiuFUdPNsVBuoU+BY984AdCLuCNmOjM2WnTHdpyHMEnLzmJrSFc2Y1y2mF9t7h6H+rGp/5WHUaYCb6vWH2a4f/8lSmiSlbZ3kVYC62J3/V8icswtQlA2M0omtLhAFKTi3sTf1ySNIxe1w0SnKxJe0H9JrXIZ5WqfxWQI6lRaZU4ZNDl1q1+0bSjMtjhAVQl0DMvUvlleB6V787Qobh4Hfg6BHNUd3gPrPkioVprVprx5XyituzPCKIS3Inek5OJGf68Xb8f32cbn6VUTFYvU/6Uo04wZqdCyxATOgnl237eQzGeaZeqsOufnFuTjyv5lY1HyiybCqe1S+qx7hVBZQqIRfz4RFGAL/44fhAbJiHWCpZ8+/o9I635Zc+t21YHdEMDB6IkSwASb9L9i6bMk7SipbTaOyGlGSEINoZIyke5xso1xbGTB3HSiTklZiRLlMAtlrdJRPeXOuRqDP2usraqN7RakNORefrs4OR8mluUEMUAOe+WTyEcycbEkOBvhE0NSPxcqVR2rDys4IrX7Q3iJ1Fc/Ru3Sfu9CopnFYYyhDxrfagZPxOxPdqlSY6sLnmCgblw9gYh5NOgHijuI+y6qwWZV6CjigUcrpftOuDzz7iGhGD2GBnfjSy4QwmOENDRxjeK9Rn2dkdPLSqMeXwf0PL799bG9DAEbNZWqPdiIBYo5yIe9ESEi1bmNT2mAm3YvlXH9pAnmoc9udyDA4CrLPDznjBnPyCndFyNvjCxyNqpIaLbJLnvdkT8qe4aIhkW1krEFw1rLfwHEwn6bjJw7yasTbnKln49FG4Bjsgbf4+3j3Pa6yxclXkgSohcsYPR9GUendckU5KzalofU4RrRMi3L3SlW5BY5Owh7GRFIzlrXLCac0lzcknE/K3Ddu7onwNEyxK7wdA+ccRbBs8Zcf4j6lPV9TQC7hbibNqcWRARnNkx3rkSGYpiNXvrG6uqBQRHCJd267fPWGEV2blJLdLp4Y4cavCKvm1ZPlzVX7ia35MV9OA6yb80M3X8rVPZyVC+ryif4+Af8LPwFKa02Y6KxAOQqFJ7zmqYuFgFFwYDJNcsft6lEBozK7+zV3heWjNQJ5agkUFLVWPuHnJtO8/0AChiJX2aI3ZfO1ZYQsOQSxZxfY5Dft6b56XTVdebKtYqdxlzKyI+v3ovcX8M7mhCLnEFVGTleylU0nYqEysal6EwDzjD6Oo0r+qGEaybss8hI8CUXqr5fH0wc9LotnoePmOADYbAIwoTEL9CY4dTHB/rpsTjBdv3kImZTprOwso3A7Kl+4W2otrxIEmV4p81kgWLn+fIzJtk7Fud3s4Lk2YaEyCkYesepeVkP5dU6tj2kb+sLu6HEW2156gyKVok11lg0nloh9Akh1qqLyvCorNYsrUKRjIfB3z6i1C3Hl8klIH8T8e/9IdfYyRVyu+BTHVVKHVqDyE3iOqB3VFGpPmUw5Vd25roK/9s5MifNk9lcwec8Vz62JH0XhYHfg0+QYVUnsR/M6KV/euLPh0dAxHfvyxwTDsP5ivC1S/y5m8yC+4cRCjaMjehoUv5Ai+YfwoBw0hW0kKFpaee8nzabaxdVNBvxfgm7241QzUWNYx8zgNq8CM2V8V64C4d5DypBE8sNNq06d63Z4qDbMs2hl7FnlcKnBFFvLiCZ+H83hVFoOhHGrfHXLsMmWlZ3PpJWsXt4dVfwRVdDwqaV1MD9sYWnWj7bGDNM/1GIwo0Th9UDfni/eeXj+rMzbrqfv8tvJYoWHLYuqVXGXPn0mqJTkWj5oqMomjPqBvnpN7lsaITZVDeVLNExi7tXx2Vi6D3LsmT6uJuGMb4B5K4wKaPn6rhFDNFKqQljRKN6g9JOy5lytYfy6WXSuhwcalAgtQ6i0Fkwy+fhf7cDEDl5QUK8RLz/1y409LhumyOKhhJFEHh1hGqYvRzuKCyl3V3tqKEy9cKdNH3nvHf8Ti69WcV9y22bNKHsVTbmSpOyDMd0TgaE7b6wtqUl5CuhXPvxOIb08dT99RG4UtOHnWGLWQn5B0EBDTCrq55F2va+pGmrTREoLbtUmjg2aogH5fgcSPyuZ5luHHuNDSUPVsVY3PHUWxIIEnvJ4i6m4VvapNb95gT1roa9OabYnHmXxF4o4yG/WuZQIHIc189h2HaYrMmBzHvdw4G6svSXHg9npVRGn671omkdazzENuUrpqNKrbqfEAwcnaYXgQSl5K8t+tP69idHFJk81d74+xTPVSbeL4iLlxatrNBQL0R8mCuyY+52aXJf5dVUHRVXneIXkfRj3GiQWk6/85m9jlmaY/a/EBtLXjx169G/mu2/z/k8zaERQ3Fb4bDu/u8cIWF4Rmwgw8LopsaVnhMk7O88FhqwYPBRc6XbYYHPG7TPH/7AjmA/jZrMrq+PK1lzGwrB3Vbx1Qz/S1SAQSHXVANd9r2M+UfB8Ouu4dUzGR7I8bNt4T1ze1l5wV26/DZ+iVo3676Om0rzYGxv1NLuOcRiLC7+v/bWQhcTzcimUlMzSduW3RAx8QSknK1S+uRGLMERRENSlKPmk/N3V4r32/LqrrZGLGZxB7kBSyxlMSJ3I0vIvF5e9e796KXmAHpVfPr1GxpFG+X98rmSBkWPCUUV34zrVSjjmTBQqbDhZ6S2akptVVnAlGpy8T840UCTHftlqieIBK9odS1M/CpHDbSyhQ47VVbVHlyDeOMDLVb7PMQ+8Rt8MGshkNg4oXsDDu9uxxu1H2ti05bIsCYWjB1ep1y76m/uiwU6K3fpVsq7/PaoVTB4Vcvmx/YkrhJVki5vs27VkI+LE1rhmH7/vFBXXHxgMOS/NsAQTd4Yfi3vY1iWzabRTixcjBKzbWCe4oA1FHjfDDmcLr2YxshYXDMslfG3W0k+XTwuW8ssbuyUT6U8WlYaEifF+FT/tHJesQyaCPZYYsb2N8OIDknk+sR8+m+rvOOIvVqCJM8/cRFiBNq3ZYSQjJt2xN4Y/kcnXSVdV5lU1mvmMNuSMM50Vkwj1sWfU4Z5epHhE4QajJvx/Q1K44eBd2P3rGKqfxbiNN4Jzj7ns0itYxJ4PclHWL947CUPCLzGVNWqjXWb9JqaC+yt2movQUKlBfebSGUO5NmjTn/tOHkFVduelIeX/wOQtXm0eC83DMUCglu729ukai/j/e6vt25FHbxebXlZoGZOBSVxtBvP+I7lfJ3b3Pjc2B7o2ilb5r00cKoIaSnY/ECek8CYQ9BACy0ndavU5ph+XDVJRkP+X+5p4V3IZSq0Ls50GIvFN7Nidd4lF3xuwqecNa53PTnyNJjQpdTCJzEZourT1sHcKowWkJwPMmRoPYiHaaCtyb4TZI6kebqJ8e24idB9JyPkse93Ww40pPKaH0EW7lGfjea84OgKVy1ukHHm3sRY/e/PQYodTWIO8OPT5D50iOttSTvtosBM1wnV76F3SYeknVSVZVrKuG6rx/kw83KCt4/N3XyEvyfWMapL/1kMFMHQdvJ5NLfjiccX/gVOwjLapw02AG+mMqIEMvI3Qrn4ZQ3zuxE2BxfzWNTUuUhy6tL38y7H9kS6akkJ4RMQZI5DdMxj3DbiQyeLpW3BZPxCrZtk8ul8C2QkFHnzFg7T7XbN1ilB2rkdZ5Qd8pNq1apFGTuzSyvrUHbnLsS8KZSS52X5pguNTMTSfeV9hT83tcLhtl9JXGLCiWIJqf4346V663mIM5vgbhnJFQqV1bn4zh8a95rrdp05fCKD01a5sJAeLujCafkAjsfUXIbnokFln6o4lCuKvmmFLEqJSEirmfolXKv55pqKdp6afkl3IBDYYUvF7Cugf8f2lYl9M5uE+93dYKvO6+CUo7JCighF925Ip8N+txRz/sX3Y9lXev51pQjHBZ8MOGC6+vV59cXw60nD8910Ylu6ZYlBxegP07PJYBRn98uk7nIiyAA=
*/