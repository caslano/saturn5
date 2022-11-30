/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the extra atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Emulated implementation of extra operations
template< typename Base, std::size_t Size, bool Signed >
struct extra_operations_emulated :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = static_cast< storage_type >(-old_val);
        return old_val;
    }

    static storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = static_cast< storage_type >(-s);
        s = new_val;
        return new_val;
    }

    static storage_type add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val += v;
        s = new_val;
        return new_val;
    }

    static storage_type sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val -= v;
        s = new_val;
        return new_val;
    }

    static storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val &= v;
        s = new_val;
        return new_val;
    }

    static storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val |= v;
        s = new_val;
        return new_val;
    }

    static storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val ^= v;
        s = new_val;
        return new_val;
    }

    static storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = static_cast< storage_type >(~old_val);
        return old_val;
    }

    static storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = static_cast< storage_type >(~s);
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!add(storage, v, order);
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!sub(storage, v, order);
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!bitwise_and(storage, v, order);
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!bitwise_or(storage, v, order);
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!bitwise_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = base_type::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = base_type::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = base_type::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, Size, Signed, false > :
    public extra_operations_emulated< Base, Size, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_

/* extra_ops_emulated.hpp
mtQYvnXILCjdsrcFlG7+3tk35X+jLD/79sTxf7b8A8R99C+V6sO2/KD5QwWyz0hZi8lELwQUBsYvaTERK2ZquAEVp7RhwUkHC1zgIlu9UuuIqhGrSTPjZLtJavALIHDPloLcdub7XETRbWs0PNCqdF6jqG7GpnSqvmuen9CttNAGrJnKBNS8EdgJMhDQqixRVC+hKyp8Cb4AjkG3tvcXyMB1wLFpjfISWShj6lsbphmApHpw4V5qoXVqqXVk4VAqnXVqMaMxFMm4x2vSC/zN7zmumDlw6/bluXhL5/uIbDLwYmr/rm2eewsLOM+t5WOq0hxAYoes0jqFTURDvbAwHvDbxNbmkYWKGY7AgR+AV9DEq9mEnJGrqRl9dXawMPBqMqGypK2yNa0QYGipDS5JVXObHUq1M2STU88tZEsADSzy0xWwlZ+cGZq35irOK/QyLmLMxkzddDMrLyTKWDBSFwRP3eklFMpmEOUwGqindBKUMkqpV3cS5DOqqAdVfdP48HXemWRw+rUb9TxnYQReDQE4XIPAQ2UA0+pOHRrgf4RF/tMQ6pgaMHsZxR6Asmtp7Ae/S0/+UxWKldo5P98JrXEEHkHrtY1/gqDzAmfMYGObOwnojsCIpcB1SezRVM1qqshUvYLxTx2ojMCZJJjSyscY6isw8sXt0BB8ciOQjuCzPG9Kt8sKdtzv5QV0VO4BwYLuSdrAjlxc47nLT4WEwI7sOqGqPf6Mm/JCS4BwxR4jWHk/XXl34VsqBfSyuPMaUhjuvimZSjFzGVT4E3g0yX8CrfEFrubtOYA9bzdBwX6dzYvZR6ntqccz9WAoeWqjzVLunocx2SGwDTzvUlaof9kwluow5xZfSApczd7zAc9bL+UzLxfbtmhBgXdLs6k8VnpVe0yGMHnyNgnoVurcnm3ynh7brFtEZ6MWtC+VbboeBA0V2EEWmCvf8wOXATOK9gyMy3HdYtkb8erloYudC2iTuqnjl30E77TuzEyjF4k7F15l46cmHWyOuLVAgaxXfUkhSbubUUDW6XoV9Xi6uEKQYYM+oShYPYS9EV2jirkMym8LnLXSy97TAM+2GiQWyq/WohmuFJQY7LBANUqHSkqkoH7gC7einf2ksSmAvqdPUmWrznrxrxXb2sJ9FYPmzsoNwLdKrbROZad7AZglpDnh6COkSf7xxnh0MVuuM0UkO0JAobPweSfRDbJde2wMFKBFv31rphXk4s+5E+zix2kZVOvPySxu7nd0LpYHtLAmKbDOryIf9/SojY05lSYMCbMl2Y5KUjAvLlQ0vtSZlOvcpZ7ENr5kmTTxt/9QGNy5u5YNL2AZaFx/qCNqXL+S5g+02N30vyT3sd0vYD4oKQmvZDFU9wSvAgpuc7cY3GcTSg8Up9zpDobtDBU+FUoZVkYVjqe+BLhPz0wRAgnxTqJSUfdhUalYkVC8MkaQui/4yC3YypBKnh5kEzmJV8mouIM+yy/pZlZdSAUOTkVwUwoft96TyomwNUtlKKOtBchtqrzRne4ePM9HnAxE+Bks+uFacDoA8Q8VG3Sn3BXXfI24uY74W8X++aGT8AZlvhN0zwxTgL2AXUCG8yeoSz+JIF/DtQUrf2h8cc95inP6apMyaB11DfERuZ20k2ov4/RRzjFkHa1Kzoe7XX+atOtgsir0h/zS83a09ncH7DRHBadL+YQ5xkEBFHctp+rxmRhVSj507Ux7e6fD+UUq13IzP5BO+T7MnhP1yATLBIV/VVLwYRjNuDTRMZ9GNM3M/xlM3uUv+4WwGXX+uL+h7cM2YiOiEWx8klZuWSKZbhWnlcXadvc8nzWH+ZMDqgOiA7IDPA8ib/i1XOtzPxonxGEDrE42N/Fput2YyXmEeTHjmFae7Mqr4gOmfMPnBvAGmOWIbIhs0i0KKutLH4bkCMMV5VoZ8rmswYNjcoRhK5/cYmUV9Gi54sfffpazxK9kEXIdGe7hRksmrFyobedw439hmFktFHi7N9LEEhjoPZcf9MEiVOGF8nptvZPcRm5Pnz4BPtvKtIYVsA/gndo7AbZTwB2xNntIJSoqLKZrk3vvjbYaGqO/Evo9c99o77q1YsPoBxsvPe+LxanzBcPj971CTnNcnl4aa9ahV6EY+vsvDphsXihL15VyM78oa9Qg0HqTRNjamECYZJFEIMCtgLZjOc6a3mThsJE+qhta1zTKxDLOwiSEfGv5dpyBZYUrr5rKVW/jkhWKVvRGiS09+lLu820obtN3QqVBMm2+gJHmnprP3qEtu1zusft2ngSqtfDxgnm0CV39lwqD8guJp/7vpJ+vvR94KdU2qCSX4RU3GMviKy+jtX4WHUvoiffxrKr/ovyGouOCWrB9aeMb5rp79ZKl++7HjzLOqs4e6ZBE/6g0AI3yWTHZ2ANqWadSpMJREiHxCLV5vJm3gxpL3q7h1LpM1IJMnlHM5sePLFy1tJ8spal930ipISWLK7wfjNwNVDN646XG9+uvZsgImkxkeY3vwgyx98ccuZx2J43dBJVMfAEmQXbmemXR28C9hWicKIQIqu8daX10WxHhM4GLB1T9cw5ZqpNl2o+xVKmZJxipAssjWr5QtDcpQPskXpOGZDTLMbal8QXpvmXiicyNmI9PCbmRWXVvMdyJ40+O1FS+484bzlsoOnd6Fszo6so3yYIH1VZsjczVzauMMr2fbQN9fEpEITV0xAe0uFtZIKzN8yK5vpL5Lw+7dtm3MTde99aZRk9louXzEROBN4tK58Zw5Ks92qr8oqR8L/hwdZ6nw5fDJSGOBEGDC7pemnBWP9N5BoCnyMbhw/gziF0MTwBXhPAHiK0Bx/YbxJaHL7qjJx6+9TOh4CBMQRxFeQvfJ4bjhMaBy4D0Fg65y82EhAM/BUERhQ4eN9jPBIGDggg1Gvk8yIAKdRClHy4vmMUEj+MlHzERPDpqGLxksCLstckzDiIiJHQkFLiH4AAxYyrEXcRLFB944WAKMYFJ8l2UfHjDYA0qZFkUO6rnskitcBnBSNm4kzgQVAE4ZzEWbMR61CX4KTE87OdScBtiRNho7+G6xbCxnyHBYXaRrL5TgSMzgVPllyQRRCJDwoT7Y1sKWg9eDzIONg7KCs4KogymDDoJPglyDPbvMvoNY8P+tCO5/kax/yCxkRaQ/dD9kPye+cG1Y7Wj3r/4DWN7kXq98ML1QvQi98JY+L3/ILSjtyO1P2uHE8ISQhV6IYQohCGELPRcCF4IUwhFCE0IQQhdCEnomRDcCtYh3DHiMfIx/DHdLWVcIjdlNfkpgifCcpBgUEUXAcwDxgPT+vTUp8O/jL6CvoK08mwFzgDLANUOgQfh164Cp41IGnTVpdmV2IXftdUlAOOCqcFemrA6cTrhVKM0YzfDWaGMo2oh7sDvIOyo3O4m/lsl7L808sL9R0rYf278h3H+mYT9Fx6bXund0666n9mzxzzl+3vvJ1TTZ5UKfwciNjcnx3+eiC0pKc7PJ8UtyccrzgfgluIQ5+Dnk+ThlwACATzi3FJcIlRC4gApPhAXLw83EMAnLsHHzwuUAPJISEr+miqIV4oL9B8kYr/4VVvg4JEk4OBRnsPBPwuCg0dThoNHL4SDx0T/Vdfh4LHK4OCxJ+HgcX49KkTBwSsK/usiNpAT+HfkqQEAf1PE/nOXf7+Oxsf5t3Q0Cw1BFwO5P4nYJqxD27yetTm5wkEv6c+TTrKIpOKo5UrVCCm+UA2Kxoli/SiCNR1/iVMWO9diw7dW9oa6cjFlZYnV0ZojFEcrERusqSnej5oxUut5hY4WnyhQY2dnUZ6KVNQ6Zq/t7PbXEP3AAwmt1qQ0piz62JIlO/koEDMtRXsYNBCv9t8dHvBRn9GWhlKfufzAHZRwTKEA/Yiwmm14X7K06COsStohvfRpoX5M2wFH5/BH9DHu1b24U/SrESlHYtiml8Np6ZAUSWuI3CtpQ+5vLRWa1zNmUNOmbFx1a9BhwuWVSMRbOYLJQwME5XfJ7CNWz81Kbi0Ii7Z8CPnI6PUMBe3QqQUsuMeza8x6u1/XW4fLZaddecSF3OK4K47JUuWLLxVKgAmizGHhay0+LS1QnjmPqEmZlJr6/qi1XN0WdDw0dt1yYax+BUeVV/0pR/AWeKxg8dG+WONrqNC52RosYy0jhICX7tlkTm//6zZemtrBV7ZEOalH8yo640e+mJHc59O0QxStnGlezznSJR476SjjjPXbAD56y0ke0I07vMFrrdzsNG52SLXjSSl8a2Nrt9evy1Z6L6aTcSjhcankWDwrpgmbW4UcORyVYcx2AFI+PF8hHEvA9kDfHs/IX/i8yNYB2Bkf6Mk/ueMDTWlX0Lfzvdi1bx8qizKViDJt1dFdAkqsrfh8EI4q1uCM7TodT2d+pYReJJVRnhC+ohsUAYV60j7sG7/UDkkMyeqfUBKLRUu+pAol995yYKFWBl8RtLMHDTFNlaEAveRfTfmXWDcbOWKl2TLG478BZvdTx3PVkhiNs25MMLkRthvh/kzN85HQPxyt+abx0cyDZsQ7mGnUg9m1PMJ4zodWIpF/gvFE5uvnNUgwp9rTer0HkK/ZvG8Vvzug0RgDcy4S541f+eVaVetyhHLEQevZlEyvR+zHxZjWAQpSKUcWoTnfsvB0qox8aqQ30LYaMUlHldXrpV1QcZs4mw9v67f0ryW7qoChNK2QrbcxxwzOHe5tXZGnTqQ8H/UoVzwHM3eIimSjwo/1vykMBsatxwU+PiTsTDxRnmDdd4g+Iuxo6Df/t9FWuTn+oq0CAP91fXGW/+u++J9/UP8O3FUurv88d5VLgk+cn1+KR1qKDyAF4OWXBPKD+CQA4kB+ABAI4v11oJDmlOCWAPEAAFw8AC4pTklucRAXtyQPJ4gPIC4txS3xH+OuImn+qn2/DhMf4OBRhf/VgwIf8O8pc8bfubvKz/c3ThYNCTUOK392V2uOYB/waCNtpwh2ibrEku3YInObFT52PqnIN7IwEr4RXCcfv7E7e7qNuo7ydRYXXti5Wa483viJf5/8xeM5Qf6o7uLX3FIJuYdZKwK8j3yTUaoWkfzDYgefbYo9uZA10lNmI57t8/KqQV9TL9pm4uVynKvuTQa7vD7Ly+tvHPLPKyjUlCd21nN8ev1KUSADKFPwtmjswSK3Y6ISetE85ur6ZTVO+bilN5b2eoBEyGI0CKg4Tvbe9nSugI7IGic5ndaKrPjzb3s1nRGBPoU4+CreRjJDTVHOtGqRcTsldPiuUn25WLvtz2PR6erxT9ZTmEMivaf3yvlL07yntx+5oHV/Hgw9cw3tD3v1pZDqa5HRo5lxqaGAAj44FK8+0AF9Rrknk1y5p+g+w2dc9LqrEPsLBrL62HdOr2HWHdagt5luv+1Vud/26mHdwaVQmCrfwvXbzGTu60mzp3aBswPRH6cYwmyweWPaLK4QToYG+gayqvGhw9cN9JU+KLFzxuXpH0raabWWRXyrKkRXw+n1L5A4/S4PsnzlWCXeD8UKRVJPkUs7vyq5EEHrIUe2Fiet+P8A0sdhmyhzAIBDS9X9dVxc3ZPwiyJBggYI7u7u7u4Q3N3p4G7BLbi7B3cITnCXxht3D9C4nzzPzDszv5kz77zn3nM/M3d3dVWtWmuv/uzu2tW9/ljf1vnk8avWbkXb38NMnH/jinWD/akunFCVYWc1FpmDJ6ID+lmo/d2Yw4Dz/w+RrX9czn+hk/7v6a3aaqpfVHXpRZ1tTOwVv/xHeivX/xf0Vu7/bnorJw/3/4beyvnfSG/Fhfgbt/gP9FYYWKi/QGtkn/6sFKE/QP8bFCPE3/xWWHRSVQxWE9F/xK7d316cbi4IjqutnrPxpvi7w8Yjhki05lXk7pc73GUQjPXwQ8vA9JHpTS8oO8+3PCt8tzDKCSqG2kZjPDxpjpKaxKC0dO80N/en1y62n2XTtLIbkpLe+bcdTEt2TRISkmnzyG79qrrV5jy/kgQ6vzodYf6fRH5AQAb1IqpAQEMHYuVDwMJBkP11BM6rf/xqHjeCMp1/k8/5uU8flxwM3XgkSIMsyZIGK/MSePaEKufGl4P258Ciuzbp+KKpMQ9UJPeQIxj5hSPgo105GXauqqOlLssRu07jQv7B+OrctJYLv1nSwkCRAsjtWjARgxY83Kw5jlKUKXbfXcPTi49jueeR8l8H3EpomJta6dLWKRNmf5oUDJPc1DSVwNyl7qs9FzfwcSNx8OwRpSwm53cD1yqMXFOlpbbDwgmCgUvV3kuFZP90/HdybjlZWP5HcW6h/l2Sf4CEhvmbc/s3ohIaCvZf+yGhIKA/oKOZfCYlY2UXVU0owPh3oNvrl78epPBi6BrydRp4SZRfOmBUy9n+qYHro66ULrTLbGszB7dmc47MZ5w0vaZJ/zmElAJqAIKTSgYmAsJWIR6R5Y+ea2n9rKU+Oe1XmtP8s7A919EnL7LSzp6GqSwr93DHzWk3R9/zUEuINonNUgBi/ogEtkwUgpMP5VpucfURKes1b7TEzuElTIFvem++qflzmOMfx5IdL0Xfc1+LiFdxOMp8IiOOsMB2rC1h4UjaWrehxtzNG+3UR0pjMlyr4Iqpr+DxOc1E5eV1/PKHck/bOuXXYdq/lcUfRY4YR8Ak4MwkoIqvEgT293ZH+9uau6MhiioIASa+9wkOUF39JuWOu/rYyROyQSAGQCHlDv+U1R+huD1ABc687Weip63VZ9tpyIoOHI+a/m/F3/Ky/0/H337455ILBQUF+Q8198+qhxSdVdTEiUwsAeMfE/GqaGiaBF2HHLvj5X9pM7iOF0IHlJZwpYVvmsdQfwtWjGfhbNxnXdadzgQyiew3HXKidR2BPIaEOMeqVOVUGfFWTZVCSbUusvo4zL0qs0EvRpwrQykc0w8oLoxGSX9L4mysDyPOUsNlOGF3ERILxCcSl6jLqbWk9RvM7Zw26o4j8l/8zorrxzj1+4B2w4k3L71nyrPBaPYA8w77Upw9Nd/VwnSzBMVrxyjj79pTSg6zpsMi8bEOkfCLy/GhDv8TkLqcbP+jCxbUXwUL4q8cof77axkaGuZfCxbE30xddFGnD2zsMBifyVSD/h1f/ZrM9ZvS+CSBa1NSw3XfH39U2jss2Em0T3GjIH9N5WtSwI9nx5/524Z8ZQl69MNfwPQWnie5eqqSxLSg7l5V6TH3yiAJ8oo/WtK5i+WbEf5PUebINZK0od9Ydm/A+izzqtbXfTOuUR01v4Pvgg3qelR3SkgkvG/5vCLOOYRFIdc+0h+3QTzizLFrpGkDvz+N73p8xErQjyrGk3Smi4dpHqnosHAfO48neIdQIcjnVfo+2+fVVRRyeU5AE6/JDflQKKq9BrcTCWP2lTiadlagbQAjmyFNktQlgppH+yJM7B4rKQumj1bxZIurffvz8Ctk8xK8FTdlrz1dFJYcBd8oTYF5oXhNCbbSaEiZDqUtIkSzZKDuTi+tWolMbMh6wdfYsP0/KmS+ifxuRWkmbtWCX6zxL4U+FB0WQhmLjQzPwYEXFkL3mfm/lc77L//O8z8gQ3H+pv7/QxGDhYSD+SfsPyTEP5SwP2dBQcOgfyBlVf2P2P8/dz48RZ/O1jWGVtak0xtM6tnB79/++r6RGwClWv6cXc9TxpXJ
*/