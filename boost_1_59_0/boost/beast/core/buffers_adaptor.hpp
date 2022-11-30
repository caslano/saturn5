//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_ADAPTOR_HPP
#define BOOST_BEAST_BUFFERS_ADAPTOR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/optional.hpp>
#include <type_traits>

namespace boost {
namespace beast {

/** Adapts a <em>MutableBufferSequence</em> into a <em>DynamicBuffer</em>.

    This class wraps a <em>MutableBufferSequence</em> to meet the requirements
    of <em>DynamicBuffer</em>. Upon construction the input and output sequences
    are empty. A copy of the mutable buffer sequence object is stored; however,
    ownership of the underlying memory is not transferred. The caller is
    responsible for making sure that referenced memory remains valid
    for the duration of any operations.

    The size of the mutable buffer sequence determines the maximum
    number of bytes which may be prepared and committed.

    @tparam MutableBufferSequence The type of mutable buffer sequence to adapt.
*/
template<class MutableBufferSequence>
class buffers_adaptor
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");

    using iter_type =
        buffers_iterator_type<MutableBufferSequence>;

    template<bool>
    class subrange;

    MutableBufferSequence bs_;
    iter_type begin_;
    iter_type out_;
    iter_type end_;
    std::size_t max_size_;
    std::size_t in_pos_ = 0;    // offset in *begin_
    std::size_t in_size_ = 0;   // size of input sequence
    std::size_t out_pos_ = 0;   // offset in *out_
    std::size_t out_end_ = 0;   // output end offset

    iter_type end_impl() const;

    buffers_adaptor(
        buffers_adaptor const& other,
        std::size_t nbegin,
        std::size_t nout,
        std::size_t nend);

public:
    /// The type of the underlying mutable buffer sequence
    using value_type = MutableBufferSequence;

    /** Construct a buffers adaptor.

        @param buffers The mutable buffer sequence to wrap. A copy of
        the object will be made, but ownership of the memory is not
        transferred.
    */
    explicit
    buffers_adaptor(MutableBufferSequence const& buffers);

    /** Constructor

        This constructs the buffer adaptor in-place from
        a list of arguments.

        @param args Arguments forwarded to the buffers constructor.
    */
    template<class... Args>
    explicit
    buffers_adaptor(boost::in_place_init_t, Args&&... args);

    /// Copy Constructor
    buffers_adaptor(buffers_adaptor const& other);

    /// Copy Assignment
    buffers_adaptor& operator=(buffers_adaptor const&);

    /// Returns the original mutable buffer sequence
    value_type const&
    value() const
    {
        return bs_;
    }

    //--------------------------------------------------------------------------

#if BOOST_BEAST_DOXYGEN
    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = __implementation_defined__;

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = __implementation_defined__;

#else
    using const_buffers_type = subrange<false>;

    using mutable_buffers_type = subrange<true>;
#endif

    /// Returns the number of readable bytes.
    std::size_t
    size() const noexcept
    {
        return in_size_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    std::size_t
    max_size() const noexcept
    {
        return max_size_;
    }
    
    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept
    {
        return max_size_;
    }

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    data() const noexcept;

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    cdata() const noexcept
    {
        return data();
    }

    /// Returns a mutable buffer sequence representing the readable bytes.
    mutable_buffers_type
    data() noexcept;

    /** Returns a mutable buffer sequence representing writable bytes.
    
        Returns a mutable buffer sequence representing the writable
        bytes containing exactly `n` bytes of storage. This function
        does not allocate memory. Instead, the storage comes from
        the underlying mutable buffer sequence.

        All buffer sequences previously obtained using @ref prepare are
        invalidated. Buffer sequences previously obtained using @ref data
        remain valid.

        @param n The desired number of bytes in the returned buffer
        sequence.

        @throws std::length_error if `size() + n` exceeds `max_size()`.

        @esafe

        Strong guarantee.
    */
    mutable_buffers_type
    prepare(std::size_t n);

    /** Append writable bytes to the readable bytes.

        Appends n bytes from the start of the writable bytes to the
        end of the readable bytes. The remainder of the writable bytes
        are discarded. If n is greater than the number of writable
        bytes, all writable bytes are appended to the readable bytes.

        All buffer sequences previously obtained using @ref prepare are
        invalidated. Buffer sequences previously obtained using @ref data
        remain valid.

        @param n The number of bytes to append. If this number
        is greater than the number of writable bytes, all
        writable bytes are appended.

        @esafe

        No-throw guarantee.
    */
    void
    commit(std::size_t n) noexcept;

    /** Remove bytes from beginning of the readable bytes.

        Removes n bytes from the beginning of the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The number of bytes to remove. If this number
        is greater than the number of readable bytes, all
        readable bytes are removed.

        @esafe

        No-throw guarantee.
    */
    void
    consume(std::size_t n) noexcept;

private:

    subrange<true>
    make_subrange(std::size_t pos, std::size_t n);

    subrange<false>
    make_subrange(std::size_t pos, std::size_t n) const;

    friend struct buffers_adaptor_test_hook;

};

} // beast
} // boost

#include <boost/beast/core/impl/buffers_adaptor.hpp>

#endif

/* buffers_adaptor.hpp
3Q6BJcvZH3R+llqfmBgUTaNpLsXJ0dNcskDebWWBe0vxrGWQsWWk3H20yZwJBXmXnhLzW9eQoAwMiuf9eUqV02KaTAOrknlfeLxFviROjAoikkJZXmsqWWjeUFDPpaa+ZOXJ0xmPNBgvxbMoF6+hUyz+IekzvLyDxeXMyRyovfcHixCxablk4SmhhGEl2oMMHd6q/sxGybRk+R3eeLaHvi7vzV9f7nFyWVsleOVcvkInNzomhpYiDyTTKqo1PqqhTlX5LFUUnV4xwvYkyDOJN4gv/cUCk+/gXkqljtRpwUSZrj8nMmqWT7wto3SQ6KSGyYys4D2VuLVNN9DlxboQX8V2Z1A9nfM8oSorNVZle8JWXlAPfQ/SVpmPdRMmqMwTvzxB+9MAm6Ujkt+gedVLXJog8Msp2Sqojm15ITMVkGT0dtPf83o5Vphkt+iTGll9VORxcJq1dFa22wEonaO228eOq+kdnfNtCKuP1Iv3NKdH77cX8neaFpBjjDyslEpMsvT47EdyOqSXtCNdQwPFsiqDQNSo8CKCjtGm5OU8W4rjF53iEF5wJ+sj7N9HQx5AGlQsXPvxV3fh5VWiNXoWW9CyxDWbk3oSXv5S3ifNoJYcLL9t1mEmIElY1Gl8idoEmKOyMrOIytP5qiIDA0MqE8rCa8SDZFgBx+pgZ5S6DvBA57tqVeAKdBzzZV7Tpp3zg3QCFWqjCUf2lJylPAPyljIdv4DaE4xKlU5JwNEqlx3Y1gDa8789F+CSjDSeUXw/AiRsFSwSQ+z0YINfXZLot38jnLg9chzhBJURqm3STTazpY9v+ujRd0bAItkWCE5xaGkoPXtSdXbxLZ/IpzKyc4JQofcI0tZ5cZFCKLRsohnG6iPOuqwgtPxhPm0s9yb7r+fpM3OuU966ejNhkQwKRDPdHwSJGjM+q97zlZQ6WA0MA1/9LYOe5RVCyMZDQn4cvrUTPekHORqglQQA9j3wnzdsn2lb0j+GRfxTRVcTN7Dx3P5rKGZ7/W3esLx+35wrxwVK4R8nMou/dpJKOS3FqbYoRnDIF8ZsZNM11kggXfWrsT3ES1SUXfLHv0KY4zO5OL+9C+IlJ+yTwID+rF9qI+LdldM0ldQqWzudmUWHtO1L0i65MJlTHc40lZQSz0c0M3MDdzFa9zOVFwSVMGffiM/XvjEyjIJkg9nHBjNLD8yaoDCgqhrFzueiz0aMj0dMsvXggGreD6jvA4+pdICErwC2pWrgsjX7i4t8o33C/RuqSgIDcTSSC/hhz8C3uT1DkHGgEXHAUb3TQSyKw1DIkIukKy60La/8wH4tLS24jnbjCwzgLg8e15knpIEo3XNlTGtFVP+qrq0sOzsMUDPAiSXi6+215W7B8sOSp2m+pBEjhwisl8p4uQ1zriousTCFN5xC/Ifd3yP9293d6ryyCyvlnsDuZmIoFKC6o4FTSOlXVlY/NY7JdT8/gvbQ09M/XTdxt7r/wxQIK9JXZW7YaSwt8cEFAwE4HA4zvOfG10s+P84URJ3b+OgS4Ll6G2c2bx9KcHf32IiNoh8XKUcAV6KH1OjEtl7cbWs5B3FE+64PdcbY3rZ3nc6538aXPo8zFEB2CdTCaSdX8wez0GhH94MxLorE9HPRc/V1S9y4OVBlryUIKYQ4gcjliM97sIc+TCsWM8MEGKIxPamVNme6g7svWmaeys4Joa/ZdLWasgC8dTn8as4L6eXT65q2lwiSeOS5ctB8E3esHveYf4UQYReVW83JSUZ2qR22rxT9va6SQmSCg2XOb3K7GwoQ1EjIp+r2w4RRTdQ2E732kAOrVe6GWLrYTz7hSI72pZ/pE3Dv/sKKggBqI+YCLAhiCaajNItH1a47v8WDDE25l4D8DqohTQcc4+w96ACqUQhojY4doYvIp+lxLc1pt3HX1wN7nwTT7ESCliw4RV8pPT1PYGOl25OwnYHUC+D2Dx+G8Mr5RPWfBZIhivKhhl4P7kdcp4NaFWLTWzN9y94dqKa0g67icNvmfAI/puizS2sbZELLeOqhyWxypg+h6TimXN1zmZmZKTU1RY2352kwCiOhiHON+FJ0/Z1DHBX3P6tcm8liihaSrxQmEDEL41CtKYhqrupamVBnMhIiCmKKloUt/qSvBBn0XZRKb89C8PJkDAR5E8rS1UnfoaNFHj1On/73BRCsLtZy1jba169fgzVCZ317nB3N43Xk9+pOf77AMXKuj6JACBa/48Qr0vl0733MYbyayfcfMqttyRQgAi8MNFbn3AyP1ltS4xAAIJKBJGtWt+BGpFRJs4v0FgMhCcnwbKnH3koj1aP3tcnN/TEoiQX5oxRa5lgDpOe0R/rurgD3Nw40n6xBPxN7TzD1EUppdV20jyOd3c2v8mrjT2uN4/jcBaHgVc9XjntQNI1Vs2G+yyhSZqKOtorAVSZKUKIQyjsI6Q8QKtA3CCldVN8QTCy+1fMvWr/Sdge44O2iDq7ZCoc7MpdCgr8zAj6uk7eGoGf+AhAsQhANfBR6RxQNfAC6RUU4jHBQi7ed2NhoqJqubg25TBKU8+sX9sZ8f2FhJZerkLxjpVpgfUsLKycTEQENLCytHcwEgMuThwvY88PDwPhws2t+HYqIjFirUV0mHABgTc/RrFAbUmiVQWNzY+XlWVhERMD+8enuqVCgdMuusb5JT7f8qYGJ/rqj1d9kuTPd2vj5HxUl4fnVzQ3d9x0KgBMaKpiqk5V2OBLRze014OPdnZ2Dw8dkvv4/9W8eNRWVYE2MECc7ByhOTsZjFHgILAkrS0st7Ba+z5mKSsOHFHm10T4SUK79kjz08h5TaWnpKDmZYL+T1ezP/h1aWA6O9+tvHnF05Vzxj9NSuIM+lM65XBfIpNmbRQwbjrHg0Z0P0W2ephHjgIob01wZCHb1NY3g2sSvBka/8nIKUlpadVHVlb7z89t+MPckn5GhAFK7wmUwjJss3waKr6+vwdDQot+d3d2v35Qkv192cUFHx8fhn3Va0uFu+LrrrzN657RF3wVG2Obmn0Zvs8vLy8bLyzmsxsawXJs2XSeG++6NcjmMOZD/uBIT6/yuTz4++v5OncCwwRiDPENV3SHU1d0R8DsjBaezfZp8f3+/OjF52t7ehvMXbwM8rMxWPXlupvGlsVdTW7Xl4oJEQJjD45oYGiQCxkZLoMTtKYzenplVUtTVoamplQPAeDCErO/u6lpgYnrd7BEVI8jNSVuTjDs5/X16hb60sBRjYakPh4J1s27tEui1VOQnMTIdjOn18roLgTbPTNFkd8HHaX/aKtPMmnMiZB2Icd/uZC2dyqLm5uGhGdk52D3f/dix33JxJQHd7fFFtLC0RFLk+qVFrfevrK2tvb6JQSEB6oz4Z2jI1FQXVnZ2RLWupDs2NbQidX1+hUwiSn11NURDRXV57kF5s1SJkLq0OAj36GwnPgcXzYAmKiLUOamDgRsyZqghhcuRxrRWnMDKQqKkpGZLFYmEoBtyhE0+507f/v0K9xli4Z9cvcujLCch8VaiQmHRB+fuu6ou25YkYRxTMeiudhEwIzf6pAb4H9b99qStmdmZUiZItO06vfCOpw+gf+IG/bXT+D2RGLSiV8FgtPA+XNDTNqRI5LhT7K9QNljlrx5nNk2hX2EM50N3QDuDhzQq9RKHObYfMtl0hLS6aXCuyE2cIt020RqtSq+UUpZIRnLZJ0DotWYPuYYiEHZUWKC4WRntenmXTBen9uIJ4eyit5+1VZVM9lccsQ9j+5LRz53Da/bmyILvMWVhYACHtBbjGeI/9nQNTfAgDe/JHNDQkBBRCTG0AIiEEBRMBqOh98C1Ht49Ipnn1SFhIxTn5wK8tY62tjVHNXhQoe9Q0SZfZ+vq212+2djlnVPTF3MxMAMPS3L4MiA2tdUfokmfZfzBAY6Jpaaap6ionktLjziAPLOxpggYem8ZmbKU/7jl5+SQDi1E1RFU9C6lnC0tL9fZBSBVWVuCtqOjYUNDDaP4fH+h0IjxhbgLgggVCuUdftZiioiNYa2v89Z2V1bG3Qu+srL2+cpEg1v5rVJFUNHJY5beB5l/4Cc+GdghVDVVQ0DwWpTXlDUxI35KZYGfj26caoyZpbtFsxRvjbUARFdBOquQ4pOd7fem0r9sTzMgHQNysU6PD57W9s7OIoNllnYfH1oDEYIVMBYJU+Uxdev5ui4+VWi3+OQRoazmy6qWKxTfLdocqKKXhll1T0Vi1kqHhW8nyJrjTQfCogoqlxvSjWnUXOHs5PLxF9C6eTg5HXq3myO+BGo+T/kATP/DOomVu/+rRQ6+7ax0G8bzhHDN4d+enFk7dZ4r/06ClLvI0duAaFWSWSQ8vJwdDa++++vX91NceXq+PwDre4wzz4+usLXVSn87PWz4kUFl5NpmeaWzojCrufd1xRSsRFAjcla2z8Ro5vp5+QTk6GwGShrZQV58q+YWusLBtcmzswrLORN9ch0y2ppmrriL09vbl2jYYGGnD4wzFrwAT8e4C5vPC8S+zxJE2bKbyodjv0XExGLBSz3Gjj1D0VYXVnK0dP/LzvwEHdL+eSiEs4cFw2w17FAHD/HVFcJUBzUuDOMvx3XTexO3RXH7vrHTumoJQjGZst3u/NzVk9e1lQO4vv+lJADqTjBiOtaXSkoSJ3kw621AwOBjOxGjYkNsLoj1zX/v3jmISk1OyB2mpaMrvHTuFAqGBbm6xnj4+ELqxhh+Vx1EHjWbkLEiiSRrGf0PkJDl+KPYoCCJsgaPm5ojI/9trlysLzLWbqnml8eOsW45P5Yny9eBNwECTxKcDAyUArkkQDa/L7AgYiQWgoNrKILEgJUvURjdz5BM+sQtwgjDGj2KfNpvbUei2IuExHiHlVeaEhoSAdkeYecD4/bw8LENK2WDbeHwMcahly270b/iXfxzTZ0FrODiQHElaQfmerl4NHp/I7+zq0FRWRlEM0/9MtbnWQDcjyTddM4fcrvjxtu7W4FDcH76Kz2Ll5d3BpMKJ8f78F+EmvdOKM+sqqpa4j1P/E1lsIsrG1vhr/rNpqv/ezki5pr/+kKHPyCiJmcHB48r92BIs8Gu92jLenExPLCor8jEHtQY4AsDU0bPtbUXFrmP7s4/4kFSGsa1o6SkgBZWanZ29jH6eDuFA1V40Q2xXhN4a+ja8M/PTxh3BljNJ4hkpfxL3O/gboOQGAFRdeZGOVZupEH3AW+srDBboDX/TOXEJ1x8efz2phSR6bhfISVw3vtemewknAoQkzNZmU6ORcohQB0+Bl5BTtIVYg92Bsb4PTc+hTyYb/RlXsryQ2S92F6jTYaCwCSiI3Z7RnLlNKOhCone9bBxHTM8kBjnj+yqTI/xTkbsXAZrGkpsnzGZAN2MaFK9DXGZ2GLOgcVDIlI6UKO85aNBAXD9yhSUhH9eZYLrAaKpZFisrC15Z3hK9ITicePn5kRys9KA3qP+ycXFASWkTc3a7YuLTAx0TD1HgbrS8m3/MPXXlEEIBIf89PjRY/77ssfy0epuFeuZv9sVQECQb7rSibi4MO/LO9Nh1jDgAqRplGFFxuvuhk6/YK1DaklORbL6/ceP6BSM3M9OxJFP/KF7X9mLQ+Dh8NtPRUUVi8sxsGeFhJqSKqTj5LTU7URAfmMl6sEEyTht8hk6RLFvNS+UURZJoi2IOszVSDEMNt99CxExNvfmc8UlMjr01O21Y3hu3bbxPB9kHSinHYjVIOoSavDlo3M63EI/93IsCARc7rnRVXwNRZIHEljAxvS+6nV3BOZLP55va2WgeNVW98Okk1Zx/p91iogtVdZ57v0AGJr4FeGxNU8DENpEKXLxdQU/aHqFbRk8Stb49cBVTq77Xc1i2ElZR0cHZvPzJEBtuOhh7XR9c9UagNiAmicKcmUpQvRs+xplTEfUtoWxQde3Y5FWQMfWmhk+28A0lvcVpZ+t5psFxMDiYEGdZmRvC3xxFe7IkSfwF1sGvRTNUt5zmXU1/yKKNQweA8M/dBPYmc3J0W0cpPEUjkI+RRUbVIPHus3Ul3Vx/VKbdBg0V0MS6f5anrYb7QRARhJhsDMbUCAYbaBL92bvhRbp8YPWaOYswQGkW7a1u+tdyGbl3AdC9fTM7+Vayhm6DQMYenkXHmwi0FQp0vAEYk8dfglUaJ5rD8Yka/hjnX/yqNCnF6JD/n4+vUOeTL+1vvZcmQjkJ36d0dmoIlh1QddeG/qfom2TqffsT/3CiF5Ca3RZmVi7Ycm9jDAJhubcnMJASwRUO1iQUdpsnx5v58xhLh5kXgT4TAOuLoY6/p+0Q2Six22b029cd5kQLKYimnH4XBTyEjEIdOFyigT53d7Z/4WB0lomkKd1AhpHoZtM92Is99/c31oVHQgCSEBg3uhZk7S+h3UCS1BJb53wZ/mOARM84ifuETj6TuN+HAKNBGDpkkSS5wN/UPiDhcOHsr4QrfCfGZpGVbjibRwanpn5HHPEZD4Fod7ZledBHM9K/XqAfj+Ohcj9U3CPhEIgy/rGhJiPBKjIwtE1OhuyW8NPUNFSTuJ/8X5LYyO6oEzKXcN305CaavdCTaf/OnjsBFPMhljpx8lllyd8CgNe/o8TTXjk9T5uekUnDZaizVnikaMe+FV1A61tr0+f3yAIqMR/mFekrBf/gUV5UKHy+Z/Zr4K+Q63BaMzZ0MBrTIYRsoPfQhkNQYfSch8NhUtveCLRWGYuwMkI8K8HU6srf6d4Q7mikU7zIxq25c8m75CbDWUlEFrP60+P9h1NFGeMvE83EjRy9GtbhdFoDgk03uPeOC+s53IsD++1C+gMwHQ76LNanHqsBdVOI4R2j5CC2QNZUdWtmAJ+sfNsuby00hI/IXgMRiGD7+YyRDsPO7vZsUa04aB7LQ0zmLURYdSXqrv3jjl2yEppekh67w/V50bagWEGepJxjR082314SZ+a66clpxwAf/wCHRJq5q5ODtKLdQKumTOGTdSijGx16Fspfbu1Lb9hbbUraShbXl4ewEYWpRiu2KGph+4pI6Fe+31fzfGxql94+AWsZqMbNGC4/gopHwxwQTsYKNJVSEkB+1mPR/j8dzY6OCsTR3oslU5BkMvUzIxsFnOK7Y/srEUjZtnEHmYStRUA8z+3VDAy4bfVb5azfydDO7MgC7D8tk6eMWDQcHK/syh0GinYhgTWZDNXFt3nrckqw5tSkIhrU8BEaKvoof3H/q5Jd7NFtq9cUXZLUmAdvadKmj32HRMKH7+BcPhfs/9Bfjgi08Rg/3AYU01UhHn7+kZKlH3zsdEDzMy+OPaT4f86HqHE/a771PT29AQJJ/ng6mhrl5WlU9PS4uHiyslO11RVXZ5p8HR3nWFt9HR1S4hbbm1tS0haenl5fYFodHZ+Iipi8n3n5Sn9PAVGib5/3OZ2FeycvSVVZc2cnp7K8ZffTf5z8TF3chLcT+1pqKgvSPBvqJiHG11ff49ay8n57fJrTOhihA+I8G+WTCUCIQcBCgjvbl+eDXz7dTGQkkA8+46q22NwwxIOwjom2NQl07PJuwtCJRKwXEyNNeqBfAIXySjIwWpgZ7yhGL03npOLmcAPsJbYh+LsA5kzDyK46unbZHeK+BXfIiAq3Y/5hqfbhCHtVzhjQQ26MjnPrzB4
*/