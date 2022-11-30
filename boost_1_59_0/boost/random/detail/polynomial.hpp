/* boost random/detail/polynomial.hpp header file
 *
 * Copyright Steven Watanabe 2014
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_DETAIL_POLYNOMIAL_HPP
#define BOOST_RANDOM_DETAIL_POLYNOMIAL_HPP

#include <cstddef>
#include <limits>
#include <vector>
#include <algorithm>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace random {
namespace detail {

class polynomial_ops {
public:
    typedef unsigned long digit_t;

    static void add(std::size_t size, const digit_t * lhs,
                       const digit_t * rhs, digit_t * output)
    {
        for(std::size_t i = 0; i < size; ++i) {
            output[i] = lhs[i] ^ rhs[i];
        }
    }

    static void add_shifted_inplace(std::size_t size, const digit_t * lhs,
                                    digit_t * output, std::size_t shift)
    {
        if(shift == 0) {
            add(size, lhs, output, output);
            return;
        }
        std::size_t bits = std::numeric_limits<digit_t>::digits;
        digit_t prev = 0;
        for(std::size_t i = 0; i < size; ++i) {
            digit_t tmp = lhs[i];
            output[i] ^= (tmp << shift) | (prev >> (bits-shift));
            prev = tmp;
        }
        output[size] ^= (prev >> (bits-shift));
    }

    static void multiply_simple(std::size_t size, const digit_t * lhs,
                                   const digit_t * rhs, digit_t * output)
    {
        std::size_t bits = std::numeric_limits<digit_t>::digits;
        for(std::size_t i = 0; i < 2*size; ++i) {
            output[i] = 0;
        }
        for(std::size_t i = 0; i < size; ++i) {
            for(std::size_t j = 0; j < bits; ++j) {
                if((lhs[i] & (digit_t(1) << j)) != 0) {
                    add_shifted_inplace(size, rhs, output + i, j);
                }
            }
        }
    }

    // memory requirements: (size - cutoff) * 4 + next_smaller
    static void multiply_karatsuba(std::size_t size,
                               const digit_t * lhs, const digit_t * rhs,
                               digit_t * output)
    {
        if(size < 64) {
            multiply_simple(size, lhs, rhs, output);
            return;
        }
        // split in half
        std::size_t cutoff = size/2;
        multiply_karatsuba(cutoff, lhs, rhs, output);
        multiply_karatsuba(size - cutoff, lhs + cutoff, rhs + cutoff,
                              output + cutoff*2);
        std::vector<digit_t> local1(size - cutoff);
        std::vector<digit_t> local2(size - cutoff);
        // combine the digits for the inner multiply
        add(cutoff, lhs, lhs + cutoff, &local1[0]);
        if(size & 1) local1[cutoff] = lhs[size - 1];
        add(cutoff, rhs + cutoff, rhs, &local2[0]);
        if(size & 1) local2[cutoff] = rhs[size - 1];
        std::vector<digit_t> local3((size - cutoff) * 2);
        multiply_karatsuba(size - cutoff, &local1[0], &local2[0], &local3[0]);
        add(cutoff * 2, output, &local3[0], &local3[0]);
        add((size - cutoff) * 2, output + cutoff*2, &local3[0], &local3[0]);
        // Finally, add the inner result
        add((size - cutoff) * 2, output + cutoff, &local3[0], output + cutoff);
    }
    
    static void multiply_add_karatsuba(std::size_t size,
                                       const digit_t * lhs, const digit_t * rhs,
                                       digit_t * output)
    {
        std::vector<digit_t> buf(size * 2);
        multiply_karatsuba(size, lhs, rhs, &buf[0]);
        add(size * 2, &buf[0], output, output);
    }

    static void multiply(const digit_t * lhs, std::size_t lhs_size,
                         const digit_t * rhs, std::size_t rhs_size,
                         digit_t * output)
    {
        std::fill_n(output, lhs_size + rhs_size, digit_t(0));
        multiply_add(lhs, lhs_size, rhs, rhs_size, output);
    }

    static void multiply_add(const digit_t * lhs, std::size_t lhs_size,
                             const digit_t * rhs, std::size_t rhs_size,
                             digit_t * output)
    {
        // split into pieces that can be passed to
        // karatsuba multiply.
        while(lhs_size != 0) {
            if(lhs_size < rhs_size) {
                std::swap(lhs, rhs);
                std::swap(lhs_size, rhs_size);
            }
            
            multiply_add_karatsuba(rhs_size, lhs, rhs, output);
            
            lhs += rhs_size;
            lhs_size -= rhs_size;
            output += rhs_size;
        }
    }

    static void copy_bits(const digit_t * x, std::size_t low, std::size_t high,
                   digit_t * out)
    {
        const std::size_t bits = std::numeric_limits<digit_t>::digits;
        std::size_t offset = low/bits;
        x += offset;
        low -= offset*bits;
        high -= offset*bits;
        std::size_t n = (high-low)/bits;
        if(low == 0) {
            for(std::size_t i = 0; i < n; ++i) {
                out[i] = x[i];
            }
        } else {
            for(std::size_t i = 0; i < n; ++i) {
                out[i] = (x[i] >> low) | (x[i+1] << (bits-low));
            }
        }
        if((high-low)%bits) {
            digit_t low_mask = (digit_t(1) << ((high-low)%bits)) - 1;
            digit_t result = (x[n] >> low);
            if(low != 0 && (n+1)*bits < high) {
                result |= (x[n+1] << (bits-low));
            }
            out[n] = (result & low_mask);
        }
    }

    static void shift_left(digit_t * val, std::size_t size, std::size_t shift)
    {
        const std::size_t bits = std::numeric_limits<digit_t>::digits;
        BOOST_ASSERT(shift > 0);
        BOOST_ASSERT(shift < bits);
        digit_t prev = 0;
        for(std::size_t i = 0; i < size; ++i) {
            digit_t tmp = val[i];
            val[i] = (prev >> (bits - shift)) | (val[i] << shift);
            prev = tmp;
        }
    }

    static digit_t sqr(digit_t val) {
        const std::size_t bits = std::numeric_limits<digit_t>::digits;
        digit_t mask = (digit_t(1) << bits/2) - 1;
        for(std::size_t i = bits; i > 1; i /= 2) {
            val = ((val & ~mask) << i/2) | (val & mask);
            mask = mask & (mask >> i/4);
            mask = mask | (mask << i/2);
        }
        return val;
    }

    static void sqr(digit_t * val, std::size_t size)
    {
        const std::size_t bits = std::numeric_limits<digit_t>::digits;
        digit_t mask = (digit_t(1) << bits/2) - 1;
        for(std::size_t i = 0; i < size; ++i) {
            digit_t x = val[size - i - 1];
            val[(size - i - 1) * 2] = sqr(x & mask);
            val[(size - i - 1) * 2 + 1] = sqr(x >> bits/2);
        }
    }

    // optimized for the case when the modulus has few bits set.
    struct sparse_mod {
        sparse_mod(const digit_t * divisor, std::size_t divisor_bits)
        {
            const std::size_t bits = std::numeric_limits<digit_t>::digits;
            _remainder_bits = divisor_bits - 1;
            for(std::size_t i = 0; i < divisor_bits; ++i) {
                if(divisor[i/bits] & (digit_t(1) << i%bits)) {
                    _bit_indices.push_back(i);
                }
            }
            BOOST_ASSERT(_bit_indices.back() == divisor_bits - 1);
            _bit_indices.pop_back();
            if(_bit_indices.empty()) {
                _block_bits = divisor_bits;
                _lower_bits = 0;
            } else {
                _block_bits = divisor_bits - _bit_indices.back() - 1;
                _lower_bits = _bit_indices.back() + 1;
            }
            
            _partial_quotient.resize((_block_bits + bits - 1)/bits);
        }
        void operator()(digit_t * dividend, std::size_t dividend_bits)
        {
            const std::size_t bits = std::numeric_limits<digit_t>::digits;
            while(dividend_bits > _remainder_bits) {
                std::size_t block_start = (std::max)(dividend_bits - _block_bits, _remainder_bits);
                std::size_t block_size = (dividend_bits - block_start + bits - 1) / bits;
                copy_bits(dividend, block_start, dividend_bits, &_partial_quotient[0]);
                for(std::size_t i = 0; i < _bit_indices.size(); ++i) {
                    std::size_t pos = _bit_indices[i] + block_start - _remainder_bits;
                    add_shifted_inplace(block_size, &_partial_quotient[0], dividend + pos/bits, pos%bits);
                }
                add_shifted_inplace(block_size, &_partial_quotient[0], dividend + block_start/bits, block_start%bits);
                dividend_bits = block_start;
            }
        }
        std::vector<digit_t> _partial_quotient;
        std::size_t _remainder_bits;
        std::size_t _block_bits;
        std::size_t _lower_bits;
        std::vector<std::size_t> _bit_indices;
    };

    // base should have the same number of bits as mod
    // base, and mod should both be able to hold a power
    // of 2 >= mod_bits.  out needs to be twice as large.
    static void mod_pow_x(boost::uintmax_t exponent, const digit_t * mod, std::size_t mod_bits, digit_t * out)
    {
        const std::size_t bits = std::numeric_limits<digit_t>::digits;
        const std::size_t n = (mod_bits + bits - 1) / bits;
        const std::size_t highbit = mod_bits - 1;
        if(exponent == 0) {
            out[0] = 1;
            std::fill_n(out + 1, n - 1, digit_t(0));
            return;
        }
        boost::uintmax_t i = std::numeric_limits<boost::uintmax_t>::digits - 1;
        while(((boost::uintmax_t(1) << i) & exponent) == 0) {
            --i;
        }
        out[0] = 2;
        std::fill_n(out + 1, n - 1, digit_t(0));
        sparse_mod m(mod, mod_bits);
        while(i--) {
            sqr(out, n);
            m(out, 2 * mod_bits - 1);
            if((boost::uintmax_t(1) << i) & exponent) {
                shift_left(out, n, 1);
                if(out[highbit / bits] & (digit_t(1) << highbit%bits))
                    add(n, out, mod, out);
            }
        }
    }
};

class polynomial
{
    typedef polynomial_ops::digit_t digit_t;
public:
    polynomial() : _size(0) {}
    class reference {
    public:
        reference(digit_t &value, int idx)
            : _value(value), _idx(idx) {}
        operator bool() const { return (_value & (digit_t(1) << _idx)) != 0; }
        reference& operator=(bool b)
        {
            if(b) {
                _value |= (digit_t(1) << _idx);
            } else {
                _value &= ~(digit_t(1) << _idx);
            }
            return *this;
        }
        reference &operator^=(bool b)
        {
            _value ^= (digit_t(b) << _idx);
            return *this;
        }

        reference &operator=(const reference &other)
        {
            return *this = static_cast<bool>(other);
        }
    private:
        digit_t &_value;
        int _idx;
    };
    reference operator[](std::size_t i)
    {
        static const std::size_t bits = std::numeric_limits<digit_t>::digits;
        ensure_bit(i);
        return reference(_storage[i/bits], i%bits);
    }
    bool operator[](std::size_t i) const
    {
        static const std::size_t bits = std::numeric_limits<digit_t>::digits;
        if(i < size())
            return (_storage[i/bits] & (digit_t(1) << (i%bits))) != 0;
        else
            return false;
    }
    std::size_t size() const
    {
        return _size;
    }
    void resize(std::size_t n)
    {
        static const std::size_t bits = std::numeric_limits<digit_t>::digits;
        _storage.resize((n + bits - 1)/bits);
        // clear the high order bits in case we're shrinking.
        if(n%bits) {
            _storage.back() &= ((digit_t(1) << (n%bits)) - 1);
        }
        _size = n;
    }
    friend polynomial operator*(const polynomial &lhs, const polynomial &rhs);
    friend polynomial mod_pow_x(boost::uintmax_t exponent, polynomial mod);
private:
    std::vector<polynomial_ops::digit_t> _storage;
    std::size_t _size;
    void ensure_bit(std::size_t i)
    {
        if(i >= size()) {
            resize(i + 1);
        }
    }
    void normalize()
    {
        while(size() && (*this)[size() - 1] == 0)
            resize(size() - 1);
    }
};

inline polynomial operator*(const polynomial &lhs, const polynomial &rhs)
{
    polynomial result;
    result._storage.resize(lhs._storage.size() + rhs._storage.size());
    polynomial_ops::multiply(&lhs._storage[0], lhs._storage.size(),
                             &rhs._storage[0], rhs._storage.size(),
                             &result._storage[0]);
    result._size = lhs._size + rhs._size;
    return result;
}

inline polynomial mod_pow_x(boost::uintmax_t exponent, polynomial mod)
{
    polynomial result;
    mod.normalize();
    std::size_t mod_size = mod.size();
    result._storage.resize(mod._storage.size() * 2);
    result._size = mod.size() * 2;
    polynomial_ops::mod_pow_x(exponent, &mod._storage[0], mod_size, &result._storage[0]);
    result.resize(mod.size() - 1);
    return result;
}

}
}
}

#endif // BOOST_RANDOM_DETAIL_POLYNOMIAL_HPP

/* polynomial.hpp
VOfhodOkiaodjL6g8Z6omEzhO/5W+Yfc9BE5fRnqGiznIqWBoGjqsDz8ai68sKy7jQLL0AxuLFyfwo9yb9hZSkTDTyulOSIbeQs4948YzFfUUHQTMyc2IbLqGmJhi+3cOu8ocPl1KQqd9gD7OYjawqfI2PX3goer5/4z+RN9UAY4u39YZRjbAzPn0p+elqmGDG9WwGfzs4dqxholvleUr01V8zwyUQ1isQFrYsE+vdu4avJZOUBJ/RfFcn3Q3BX0fJi6IyZYIaO7xe2EOU6IaR1Jqa6dRVit0gOelfj3rBfGzcc4hNgyycbGgCnHyF+u+VkHPHH0Yo0r0bVnuSKN68Pig5GizLtBHzTY2Plck+I2nyqD6tfZPRDRSMkR40oOMcdgYG2vuAj56zn6HOQKkbtqXyWJgy72ZjpS16DafgK9rf9jJgEHaUYIG5Hzn1xrDPabl6O3xs2QmbmNOKEcXO9vTj5NFxdeAjNExXbxt8lCoq+T5DQrpjmlscVn6OtojsUeQFFA+GlMKE1VQJhrSTWYUD2WO+mSJQFIVQArRyVn4xPUZi6PJ+w+y1TAeaKHWAU149xExTuctxy0Zh8J7kKBX7W54gRbXya0+hvDmbpKRnbhfs+TQBVjH0XxMFOsNIqQHbsThW/BrHAHBs8FilGJDszv8UabwoQ8HVvTbAxFLXQIRJOTpYwGhVrAZ4iVTGjz+Pp2vvNskJLew4SZKN2Sh4COQiBy6c4DjMS1WuHMU/8vOADA72+1D7y3smjrnWxSaxpbPACtGqVGy99NNmApWPNFJbTQlRfBkBS01lUZsDfIJ2GXU9AYYB3dIArldV9pO9uhI2v/a6wSUh1ObWyGACKyTLnRaqldkl0pTEHLcuxzmt0uptz/3H31wu/Dv+hJymA2m83m/D2dDn4Et00oUXDJQulO7Nh8vz71veaUTKwegHGHLX44C32xoqE1gJLQqs/BXWVzwSaJKAEncRVxkoeUABTuzwfl5B78fYstHcnb4lthsfHAy3J1PrOvegF0srfRxPvamdNpCElpbbM7OqJmKgH2MomwcNI0K1/6dT5rV1Tb2lMVp2GZ8ZmjqBrGaQzzKVe7UsP9pDmYk0lE8fSBe6LVHLwdgoZuGXJq31XagrHT0z9+1nN/NWTfaNAdqkk4UatL7dlPOVi195lvhv0JuWGXTN0kR5j/Rt63IBaaSFWLbmQSq48FDXv4jz/OopAhc/Al9L+Ur+G0C28Y74iR5YnYHIhNJDowhoS0f/00SjtQO+uXWULh5IWdsi7dOufr6Di6GJkQtwMJmw+QWq7oBKBBlo7d0S5E9A5f1TfBrYjiZdow1lvv4Il0lzbIEoYuvY4oMvPR92yyNXzFaviqVXFVK7SVRRu7xdPhWBlFGbRJmgmSyV/re18XENTc03Z91frA7mp9jQYkvV7nupyRz6SK7Cl469HeXsr1VEhXKCiju8R1R/Y+kNVMG4J8D/ogBLhUZIQYg2S2PxJs+xRS4Up6vWBSRLFq7DA2yIhM6YgM7YCz9a8sMbRzt+XyARsOywcgdaPiGTNJquq4y+X4SGYLW99ZuwELOMdxupE52oPM+aV+ergpNStTtQNMWM+CP9JUylAa9m7mcyIDMmjBcCBvOipp+y32ul2AfUJqcRxwHQFJLdYVtu0pmBuCNktkFGq4z4cmiHRhevfV/Y+5wqWKavTc5Vy5+2Z0BTeOPHp8OJ65/Hmsj9C+ZiK1sPwB19G9/igONnRDo9D5R/WlOttH5WkPJJIT/2ppxdYUV1aQcOdwaEFjaSuPzJ1hfG1Q9e3YOuEqao8WCKcduvsbNF1wFgPlGdZs89CqxZsjeKn8cxP2CySe1dJRc+C23nCBmOHVgDu9mZFOyRlx3oiCBPCg1upmJengTxHIxIeeWYfSGQ+5RNL5odLFA7WJV8LsT4+e2MPpGut3exvdd1gV2D2VA8uZAwZ2vgaF688z35X6haBvkHUZ1u6B1gjZmOJP6JYCxQts7hDG88XJSgjuX2EVJhqK+ht29s8jfzCmVsMbr0FjccHE7Zg6cOhROFqxcHIkamtAY9FhYm3364TEneYnK93qbApRadLZVXTBm/SB1+sjd3DB3qbquoEUtvH5SrzHKv+51miwibvb4sE6qpxvVIzLFphF3cXBh/InW2m9qdwZGN6ZmEBES03dhI4QoQke6Lf1kyNgmpA7xHwgRUaHpBDgKXKYzgofmCcCJV36EsO2PfyHZiZFQ5HneIohQAKmTdvyH6A/+PpLpP4QV6ah49CRhmfyvQMJTyham1T74P4KSF11J2v1ynGYTk2m3kcKVEqlNutINGiCZsdXAp5sFq51zDRDV89XaEs/B3OpwYwPlVBuZFydUdEo0dWHqPtVO+SG+6qMdo9sE34Djxp8I1HKqz7ekruZVl8oLZ43BFceaxLm8OAAkUm+eUXCm035jxYoa6GYtg+impNgC5n4d9FabP2oiXaTVg88iU5SEalwYSxxrGebFu6RcJpUfj6cYBU0gvtzb7mmNmUTdgEBLNSgVn3UTDpmxx4NCwidqa4vqMAbRVr9CXNGFWtjE7pHR2fMP4csL2z8KQCtelaqT4BFe+8MxqSaCdDqFlwyYMlYMzY4qhTRi9KBElPFD2oK2A4jrWHVurjoMxrZlLewNjMpjr13F9q2Qe/fxzOGvTKb5xC4DaQbwVgPBYniPMIkvmYwPo8t3QolAuJDrkknNqAz2ljJVmU5O4EHMRzxnf7MsTiLzSXsSrGAyovglWq50rOJcm1DQv0BnJwCh2JzxDz+wzQA6Z2Q77s6osTlhQgU13GBnBOscoSNvR8cmWDp01hGhubU98ch8mQlQlxX4aLrRiWS3crgagyyXa1gkQkzsX7YaTCKSeEEbmJ5F2dRHF1bH57ZWxYDcU2oxlhRA567TgdGWRjtd3g2lPuge9K4wO9eNPVY6dY2CnWLKRO2zLFMo8ysu2NtR8V9obGhdFSul0bTa8Qrdm+iN7poKXzuGO4nmhcmg+X1y/fjvCXveAclNTDXcI12S1G7N3/HuLWzPINgvlEhfF7aov+iEOzqdZJBr0j5He9gq8GCQRg0uC/YTizx82TKV3ImWx+WOSzRGagLWzIoVJhJDALRbNYPVezlg3cCVN5/0CsI0GyFDfv1+EEonHmiy9lCWKWvi95AmJ2Il9k35Pwb66Yfy1EdC7f03ZuvunWfNDArYyUn3ev6CViwTOcjPyS8/lHTSflNEGLMLS5wGSEDJ4rnDwb25BfiNHI3JtxxftSEugaRVlAEimaSepNPa4Vhl9X+Nqa7hpuLfyHL9AwTii9pIE63R8Ouse3Hv+OYayCWNZZbNOIGGbY/rm/SSow9CbVVj8N0XHSVc+7aHrejUHbkrI3JGdPzwHw3mpSWg15NWwk/M9EF1fURcn6dDEotDB+ZkPtUg12kXERMp777AaJdiXnp35FQzyhRz1iWqNYkr0ghq7e+WEGvTFZPbmFlwWgb1rh2AxYV6QFKKGOh3Z8VnCcLs1Fc6PERk5fOmH1SI48LmuF/KDRuflW0p6ZXmzYiJXFNDUv9c0nF0TQFSwjGKuNDJ71j48Pz8o8kVV7WVNaYUHFZVVFTaVbIUVSZwLIT7gdU3oEAHg9foxIUy1YJ0pW1GANMkChZKQ3goZhRvr78Jnv21ezZm/5UhQwRuVBJTtD9mOr+jk0P8Kvso7xLHYyLaovJ8i/L7x/Hfg5EJ0lmFWcN7mnQ9M6abBtou8TTQvLi8HFdNEP3cV0yo/cZPUeuMXSBh5IBYZ4QMFhc5mVKybpYksrTJIF+mo3oS9/llIzA+g7BOMD7NmFvqR4qDCsI/70A07BKiMnRsF979cnsJA+zPF4sy+J7PGfO4xtbOgNJrvnPnsWWtgvTnb+xlv0d1GFFn+cwTortXxLyGGkFa2OnGZxgZlgeq6nLHJCnrkge7dOGVJ7N08QFsgn81hz2AL5lcMc3wNlLHjTYDO1WuLGV4/D0eQQOQEJoaNAWimdpLAh6DMuy4YkXTL5WOI7AbjTZEN/xfCclZSLBehb9ELc3swjtsTy9XAqIbIFAaKCsin0YhURY4IoKQh71z0KQQC4gHIdEHX24epIG/tcExjoMMM8TzeoC5pXbE43GLaFnLtQcEvwAs8XwIk8vUu67FcOLGKG74M3mZU/vIILSjJIXDqpheUYuIjwaS9isuaCTYXnIpN6opr0/q7GrlSDnYDitDmPufROLI4qknlqWonOlebXgVkP1IJRldWYJM/a4r5KuAYKVHvI6gaLfkPpqi1loERRTAMwFjKp2yX7fusv+Y2GpO45V0pfbEbZlWtmCE4gmCxTp3CdjTDaxcT8AwU5SoamCKFhyh/lDQMXYmE4akSh+00pScJuUw8Jg1yd48KQ68RwSFcGNXCBpt9CpcC+YBWKyJv0k4yp44lDE5WaxXATWChayPYkVkiP9fq20LODox6WaQbVlBurZEw5oieu/LsEOEW3bUzM8gJD6bRRcNAaR7MatsT4v7Hxd6KAfKk9qfLzLNZUxNQDdzrNZviJVJ5vnj773NkQxZIoIjtauju8AGSbBfM7ujzc581h5A4g0gFiOgV2RE/ZVgZPLGiV79N9jtcWmH3IDvksqhCHF8IMwDr9YV5sHJYVF2YrH/SWB2GN2buWSeT5mV1StadJde95aZ3XyOl7QIfjBbTfLAdd/TL+L/4nlWykiCLsxNc9h9YRcvW4M+orTw56aC6J1DHgMJvAM2hW4nSD9ftxYe+dR9eLDtQagEWgBJ8kIMP91NHBtPZRvzLbYCC8wc1Jd6Rv4PpTNBr35kkxH43PZZO5ER1otK/pHAdrpb0Qt5BL0AvpyGPDW+QJgOwLncnFoE0na5+aQnuBK/g/iS3KiD0LRn02JgnHkmjis8pFPX8ghpNqaZriqPNmUbt+noH6O7ctYEbT+7P3GE/1q0TF5FH+/UGptp6nDnLVvqOmfgM5XQV3/cbut3Mh41XrKs9a7PkDrVStuw1vlbUvRKq2F03sRnRoSppsvbSqMk5zqqJKGocwtazsVMcuBI5qZszxn3FBCllf3lQGfL1O7UpY8Reqk7/zE2qk2jh/qXPmUQjWw0ptbukgLl7pYVk1sG/L0Kubl+ZJYwZv9TyMfLKcWYUA/VHzc7D1guWU9zYeiOtVXmIdVK75j2pbCpPUo6BfHR3J9OaNKtQj6HCGZldG6i9WMSlnoB5LSTXa+ARXbbCTpa2kKrUTMKQ4jBmMfbu+/ie2LJ5pVj2EV+uqHyCBb+zWeHLY099D4sX/6cdDyI8nfKWds6hVmTRjqglMsosUfo0vkyTc+TLTmgMDT+Rzc5VzrTlRtoeJRGfBVhyXdI6ICDZ4/qiL2PxmTKnXca47b2FR/QArn7Hb3a7h9/0u2bBN8OcrJPsjoXhb/RimZ0ys6vlZ4s4gjmphgcW0fcWAkOlieuMbwqh6aATRmwM8dthnwXL/hFk0aC+Lf11WVCXHv6Fq54QZMDQ+5bF4ndWi1XCc06iPu9unL/6CDyZjvcVnHx7Mgj80NTBWqKcvhK7dInVe23r+HFI5zmYFOLYWnz/zyMEQo+bi0PDLTNGI64O6X0AFEcXNkrdDOGQVwPXd20gDWxH6jOjLfvTTAV0VngNK3KCMsWpfpeIGV2PlWntGyRZwLUTAmCsthhPyW4IBlDxXN4TaT1Sn2ieq4u6ri6qtiIc2lcuvSmo/1bL/xnxabvrx7/hnR/2h5f2GorxE7HXaSNrszVxeTk8wzkq9c1mzBpm6WDUCbprwronNY/sA2iWt1sNEQEvkBXaKv+3GPAAW+H9ZovsUU7V+zIZfLUmRSfbU5A4Bs546KDU3prysPT6k/gCdUxtyB3j+YD0z14ZZ2sWAOrglJQ2r5+LfTFG/KttuKj61dVxs2O4aSHiHgUBtpib+pHm4lHGpHew1oV56u4+BKBgVSYRZGKjrxAH7zSCJ21HwBGnBePcBdLSpF6SG5Zs2Kkbso44Q1+JVrHPMJVryGklGkwO/9nLkxyK2psfdBBSCRaTOOImxLCdOkFeyRN++bXrEDVy1H33Kk2mPtLZH7tVDS0ZxG7KZCu+mSfxq9HUqdS7hYQz5bRoL6g8J8PVtGz9tEyD1CTF8Ju0gSBggGb4qLON2AFDyZsBtCIq8NWhVg8ll9qd8dCw7fBISdx9xrHHiZCh1gBQTKrUnXRwxHNUTMV4ZNF3LjUMGidM/iE1K6oCEMf6PZyxz676WDe+vuLLGhAEfEArrj32qs4NvxSbL4edg/esx78/1ncvGYMO+gnrPJx5HmXqGprRgo7AklqIoGKP19KBt9JaKz9S7sB34E/hQJwMsPmBm6lFfxeBrnr8cewxCIHas8yF/muLIAqW8yqIE4z64oC49zrVz1ej93Wma0ltWSszWRvD35WP+ac8yqD9xK2JXq14NMDAdyz8+MXJWf4dUb8mAuBVAW7La9F3dzv4W7JPMv73HahABHGtV2uG/w0+oyUvv5a6qL0feZQuKm9I4JA2bkdLBKYZhrtfyAyhuC+klr61gjTzALRd7fA0YI2AS8jx7CfHCxvM6hCk4HC3GsyNbXK54tA0brTjH55912QK8GE3IU34lP7JWwcOw2jGgNeSANYt2UHV9U13oUNoH8SjY1ZotSpy9E1ZpUBe7hFgXGmw8Qb6gqeK9IY10sJM5y8nwgHOGbB1Oi7zzEcycNNZqCCrDaJfh3tbBqTxsctLtx4QZewhfS2wjx5QGbcpA/FvWsooAIJXxU5QEcN2vkXMQbZRfOUg1ebjRAX1JpbIwrMQFCKTvuW2WJC+7QE2/TGmT7IexpiAVZuIcBZGHZtVB/1lPR9AF1CKDDGX60JV7n8Q0KYOKJcjNabwEL6tHGlMm+9HJzOrY8FvbrduiJkfYLP/pi+94aiyVXNuI+uxe+zC6IL1GTWFngwjY10IplDU36jS1ZhiNM25q8P3l7UHeKMbFrZFdduX/1IP3HHMgLthf81ZZaLf3b6cmv9bzbA8F/Dq6XXAABwAmoX0VHmNKrgYuOvFHbdy4krtDpPdWORUe3/DEL55OCRftaFjT8M5Gg15X+YRXNq8jkqC3RgHptFUGDYtgj61YUbxNG6cWGySo+jo38UbGUBmNz16zCJ1coVqK0RETHW43u1TzrQfAroIQnWZMXD1+K1pn5WZJ3cOwXD6SMno942dy9f7+A8j78PVwuoI8CLbY/WXdUfzMl0Rxu8C2qbF7u4eD4OmiyFXmBsJ9AqAMo766zzhgLrKvM1VJrKah81+FgEUbTRV1ues8fZN/ptFSKZ4vUu+PaHFHHBCTKYIZ2kOhN4XWEevUOqF5oAD5yOxCm3p5Uy1HvDobYkMa/pQTM+Ktwpz+7Ll/BMIn9FssWVL07/p8MA7GKTSrNgQpyYm9qiGIcEbxfYJGccTBCr5kwKGKT2KM26lUrIy1ea+uyrSBnILYCkZJlhU/4OnpEI5+oNbU6udQLpsiErgLR1WvQVyPLooawkB2BUah5pztAxqG/1lck5LmQiH3GfSz9xziDKlJoheBWM6AbqeQO/jF+8eKq8bXLfNxvCI3SZEwhjXcGYSxoJN9qIV8HyhiEMEe4oLOx+b2nVtgWaCy2viShlAItbbse
*/