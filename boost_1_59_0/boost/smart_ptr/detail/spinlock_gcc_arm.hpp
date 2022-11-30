#ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_GCC_ARM_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SPINLOCK_GCC_ARM_HPP_INCLUDED

//
//  Copyright (c) 2008, 2011 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/yield_k.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using g++/ARM spinlock")

#endif

#if defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7S__)

# define BOOST_SP_ARM_BARRIER "dmb"
# define BOOST_SP_ARM_HAS_LDREX

#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__)

# define BOOST_SP_ARM_BARRIER "mcr p15, 0, r0, c7, c10, 5"
# define BOOST_SP_ARM_HAS_LDREX

#else

# define BOOST_SP_ARM_BARRIER ""

#endif

namespace boost
{

namespace detail
{

class spinlock
{
public:

    int v_;

public:

    bool try_lock()
    {
        int r;

#ifdef BOOST_SP_ARM_HAS_LDREX

        __asm__ __volatile__(
            "ldrex %0, [%2]; \n"
            "cmp %0, %1; \n"
            "strexne %0, %1, [%2]; \n"
            BOOST_SP_ARM_BARRIER :
            "=&r"( r ): // outputs
            "r"( 1 ), "r"( &v_ ): // inputs
            "memory", "cc" );

#else

        __asm__ __volatile__(
            "swp %0, %1, [%2];\n"
            BOOST_SP_ARM_BARRIER :
            "=&r"( r ): // outputs
            "r"( 1 ), "r"( &v_ ): // inputs
            "memory", "cc" );

#endif

        return r == 0;
    }

    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }

    void unlock()
    {
        __asm__ __volatile__( BOOST_SP_ARM_BARRIER ::: "memory" );
        *const_cast< int volatile* >( &v_ ) = 0;
        __asm__ __volatile__( BOOST_SP_ARM_BARRIER ::: "memory" );
    }

public:

    class scoped_lock
    {
    private:

        spinlock & sp_;

        scoped_lock( scoped_lock const & );
        scoped_lock & operator=( scoped_lock const & );

    public:

        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }

        ~scoped_lock()
        {
            sp_.unlock();
        }
    };
};

} // namespace detail
} // namespace boost

#define BOOST_DETAIL_SPINLOCK_INIT {0}

#undef BOOST_SP_ARM_BARRIER
#undef BOOST_SP_ARM_HAS_LDREX

#endif // #ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_GCC_ARM_HPP_INCLUDED

/* spinlock_gcc_arm.hpp
FyBtxSLkrgrDyai/42TMMhREvoTilS+hcuUcFKwyoCTqZRT8cyFK3whDQcwSFMcuRgXZqIwJg23VMlxYuxyl6yJQ+eZSrFq1CjExMXg3djXWrVuHzZs3Y+vKFdSWCR++8Tr2rXkD/9r8PhI2b8K2bduwc/t2fPbZZ/jqs3gkJCQgMTERF2NWojjahMrVK1Hw1gqUvBOJkg2r/s3eW4BXkXRro4W7h+AQ3KHduzfuwd3dneDuroM7w+Cug7u7BHdIcElCcKn7Vu9sCDOMfOec+597n+dvnsXO7q6uWlW1aq33raruTUKmTSAP5owlz+eMJq9nDydP500nryEvFk4grxeNI8+WTCcRy2eQyPULyIX1a8il3zeT4N07ydM1i0jE6sXk5aalJHzLMhKxcwMJObCXvN23kxw6dIgcP3yYnDx5kgQfPUIuXrxIbt26RR4dPkCeHjtC3h/eRyKPHSIfThwlb04dJ+Hnz5DnVy6R0GtXycfLF0nkrRvk0/WrJCQkhDx79oxEPgwln0NDSNjjR8A+r0hkZCT5EPmafPnyxR33/yvrTl1kReFwKIpcf9E/JW4guGm/HUqJv7ulZPr0biq+PDt49+/0+sK/SN0tfXo38/LfD7eI9PV/mlxO782dx+HNH4dbQnrhJ0ohtTd7PvrhLSB9+lrfE35Pnj5DVPKoykb9mYFd+kPcSePvS+8q4J86dWp/f2953vQ/liCm8qbP4KZOlsl7JHMrlMFN758mWh1KpPKm9x5JM+XOkQ1H9kxJv5/0TyV+S/5bbKT3811JlSzTtQPbtm37vWamzKl8J/38U6Wq6ksfLxVLn+57+nuPQ0NCjuzJlDl21Ll0LH3qKI2CYrP8vykUO3OmJ29wPNr/PX16f6SPXc+bPq43ve9A+qdvcby5gfTfTyO9l7Uvjf2H9IkyHb/AjmOZEv0hPfv9BlLQTf/9htgxo5ozU6bY39OnYundqBvzj+mTZqpg58yRI0d25P/ttJs+9q/e9KmiH7EzZnp4aAfas0amxDF+vBK7Olrnj+njJs8S9vbRo9Cj23NlSRjzx/RVCKnnTc/KTC9IeunSRpHAV5/QPo+P1AkMtPKLQvrvCgFEJPCmTy/Ipb1HCU/grU+44U3ogbrNAosWLFm6lIx73PRo0TgseVZfYhwl9cA27z7hjjehh3Y1CzRLlGRnZcG9wa1uQPGSvsQsfYmigf1ff2J3PDq0OzDQiLqoB0Sl1xs0ahSV1HugBi1eRt0wNtD0ZVZSYunjlezesWP7Ro3KsuSmexiFPIGBz9kNb0L2Bhb9VnhJEemNXj27d+/cuVOHDqWLBkYdRQuogZtY+k+PDgdWKFGGHW7xqQnpOnlC7949euCORoGtpo4bi6NZYL68gfPd9G+ONg/0pi/DFDAI4tCUKVN6Dx06tHOj5tPehh45cmjnmMDACoEXvelDmgeW9KZHCXo72EOvJUsWz52LGzq2aPH5y9s3b0L2NQ0M7Bf+6RPc+NuQwGjp5V+QvuHmdWtWsTt6tG51H0k+vQ09dOBg6BuW/Mvb64HNyrbEUZkp5L55vvvJk+yOVbOH9mi74It7w5vHb966yb+8PRNY1E3fkqUv7g6YJWdPntyyfu2qxVMGtr375cfjQ5vA0h364GjZoUxZfbybvvvly+dOn8IdiycOmhbxY/oTgUUb9fGll9zk5OzZy5eDz53esmXt4hnTpr2InvxWYGDpPr70pSZ405PuN2+yO85v3bJmzvRBJ977Ur9fgOSdvqX/RgvIkps3b165cun8+S1r5s6cNujis/dfPkbe3RAY2MyXvE+HDp5l39KvQ/pbt9gdbhHT+rdt06pF80Cf7t7so/9EyuLbOHDHJdyxftXcGbijdZMmnfv06ds3KvsypaMlJ2Ti3Tt3cMcV9461a9F9I4eOGDGkry99NOW9xxTvDa5S57du3Lhy5bx5o0ePjkrf4c+789bd9N3Bioi6Y8QIdkPLMp3/lJyQk5fvsjuueuvt3jB71IgRQzt3LjPxJ8lxrLvzQxFrYVOjYOc/yzzq2Oze4a3FqS1rV6+aO7Tz2b9OjmPdqZusiJvo71NbVg0d+reJvcfJNWvmrlo8dO7iNT+7St0j+uegbyRtIPtkxIp97mOT1sTdO8X2dTLkFAP/uT/QgE/3ia6B7vvh2NKau8+Ffd5ln1miPpNF7bGK9jmIfcb7w2es75/kf/hzUPTPaOXui/4ZTb+77DNLVH18n56oeg6MqndUO7D2YO3its8g795Xejeq/djkO/v0TrgT7+T6H/fi/v18+lZw1J2Mo3J+5HcxPdmjZCS7zOxkpycvOVIoNTmR148cK+xPzhROQ27lTk3O4fNKoTTkdv405DA46glw1FPgokfBTY8p6cBX05GTWlpyRgdfBVc9YWUh5/Q05DyXlgTzacklCdwV14KNtOQC+OslOz254skIHpueXMVnCHhwSP4M5KQnO7ku5CAPhGzksVWIzAl0yNai+cjuEvnJrmIFyK+BNtlcTiE7y4tkN3jrjSIZyDVw11vgrrdLZCZ3i4PD4jOkVBZytEhOcNns5FSRrPjMSY6A0x4tlY8cKl2YnCyZl5wuW4icK5aNBBfLSs6VzAluK5CDFTRyHPz2YimFBIPP3iqFv8viM9BwOS3js+eqePnszaoWCa79nc/eB58NKWuRubXLk2W1SpLVdUqSZXXLkoX1K5LlDSqQLbWKkt01K5INjQLJnkYVyd7alcmexhXIksZVycpm1ciSlnXIytZ1ye8dGpBl3dqQNeC8e4Kakx39OpFdPTrjswfZNLAv2V+xBDlUqxg5UasIOd6gNAmuX4zcBvc9At57s25lch/c93HFouRelRLkaZWSLv+9V7MceV6rPLlfvzw53KQSudGkFDnfuBy52bwcudOmEgnugHvbVScXW9QnF8Bzb3VrQB40AYduXoK8al2KPGhTjjxrW47cb16FPGxRh7xoUZc8aVefhHauTp53rkpCejQgz3rUJa961yNhXauSa+2akhs9If1bkRtd25Kr/duSa326knudWpIXHZqS+32akRf9m5LQnq3Jy6C2JLR/axLWuQUJ69+EhPXuRML6diHzhg4gwUM6kVvDupJbIwaSW2N6g8O2Jy/AYSOGtSavR3cioSMYh+1Jno0NArftR0LG9yWPJ/YFj+1BwsZ0JWHD+pDnU/qRiCl9yNThQ8m84YPI3IkTyNy5c8nuMSPIthnTyK45s8jvy5aSXcuXkg0bNpDtWzaTnTt3krNTRpKHE0eR8LFDyFNw1YczR5Bns0aQkNljybO5Y0jkjEEkYvYw8nr+aPJg3hTycvYv4K9TSMSiCeTRr1PJ09+mgrvOIi9WzSURS34hkStmgK/OJZc2byC3wWHfLFtEwlcsJi/W/0pebVlOwjcuJhGb15HwbavIEXDXU+Culy5dIteuXSOPz5wiH44eJA/PnyVPz50hd2/eIK+DL5APVy+TyHt3yIMHD8hTcFU2Z/7pYQh5jc/PL1+Q169fk48R4eTDhw/ky4cP/zFPbdWgbsM69Vr9/GKzEpLvKNH4T1dbl8gmSZpWo0YNTUMKT4sfL1vZ3MtRBxJk41dGu+zJli2He53l7r2ereD3y6n93etStkyZEiXJxLICsfIvuDfqspAqJWhWjhzZkuTNgyMZ+xPXU3Hey10YDGdELGXiNUf379+TMxX7kj5lqlQt3euxcD0lSsiWKvHJN8+fHc6ZyE2Ms+wdNKQJu+49Em8NCwu7lzO+73us5rge9/v1RPl69+5dK/G3E7EQF07E+P41cf8eTRt1jnadxZNo13Ndenr86L5ciXxnYsVqQwrGwjc/f6tYqSplyl/+9O7dkw69ynqK5vb3Ywlqk9ixUqUuWqpyFRyVKkz+8Ondm2OdalWoVKVUMQvX85MYcUpVquIelSqVKf9bBLDyk461yrATZYxYhUncrkOCgthVFwrXmhyJBEd6VvDe4SlMuo0aPmLo4KDAvv379OlViyv/AGj76azAKtWrV0eCemTUvNmjRwwb2mfr3UMHO/YqV/MRrj+fG1itOktQpi25NG/1ukXTRgzc+RmqHxg5nwHk8AWB1d3rpdB+q3/fvG7dohELX3/58u7Z0+cMP7+aVKV6v35R19eeO7Nry/pFk059/gZnb9SqNmbMmO7VqzCcTy5dO39615ZFC+/7ErweEDjGve7yTrL6xo1r5y/uWrdw+UtA3I+vr/QN7D52LLve3r1OzoXcvHX14q5Ni5duP3VqxeRaVceMZderB/ns71rowztuiiULF04cOn4CYytjun+7TK7dfPzwzp1bwRd2b1m/bMbMmRNwuV/1b5dZisdIcfvqxd27N25YNmPqhDHdh0e/TMh5JEAhwRd370AWvwyd8+NlHDdvsgRXz+7asmTRqj9dZUfI2dO/b1u36ffvZ0gUPmPbQgDP2Bx31By6J2oOPdm+qHX/QVHz4sQr0fcI/FF8+wXcOXQmLB/fXoHP0ebS2R4AhlPYrmQ2GH04hT32+u2IhlN+L5iKbAdO2VnIz4tVhHRktxFAdlo5yf78fmQfzp8umJoE52EYxZ9cA0bZz/uRQ0JqckTyzqWfUv2BTdKQM5DDDK/IaclRMzOwSjpy3MxCzjOcogKXMGwCXMKwyWXHi03uAZfcK5CR3CqclRy0s5N9Zg5yzubJPSE7uaflISFGfrKnSB6yp5RANpZXyDbgknVVPGRXDQ+5VtSLS26VyOLOq7uYpFhucrIYsEbxnORQsTxkX8n85EgpNseelQSXyEbOBvLkWEWVHC6vkWPAIdeBP66XAf4op5PDVUxyrIpBTgODnK1hkLM1LXKuquZikcs1TXK+FvAI5Foth9yqbpNztT3kcl2HXK9jkzv1PS5GeVREIPdLGyS0tE4e4zOkrEmelrW9c+/1SpLdwBN7q5cni9vUJztaVCM7WtYg65vVJwvaNiHzOrcks7u1J5taNibbeweRrQN6kzvVigB7FCVXG5UkDwOLkPs1ipHQmqVdzPGsRlnyvE4gedKgCnlevzK53Lw8udWyPLnduCK50LY6udO+GjnSuSE537kBudOtLrnZrT651b0RCQXueNi0hIs9XrREvq3Lk1dtypLHTWqSJ8BIz1vVI886VyOvutciD4LqAUM0AO6oT170awQMUZkc7tiKXIa+R7o2I8cHdCTXejcnB3t2Ifv79yRn+vfAPc3J46AW7lz6S+Csh33aklXD+5MtowaQ26N6kntDOpKnQ9qQ50PbkCfAGuGDW5KHo4PIszHdyKtx3cjjsd3JC+CNiNGdSfiwviR0ykDybDJwxi/9SSRwRvi0AWT3uFFk0aJFZOXKleT8iEHk5pRh5Mi0yeTJmCHk3pQh5O70ESR0xkjydBqwxYxh5NnsUeTpvLEkfMYQEjZ7OImERMyYSMLnjyFvgC9eLZpIXi8cRyIXTySPF00mjxcDWyydTp6tmENeLJ9Jnq5eQCKX/kLCl04l4cunk8hVs0j4mvlk/5ZN5MzuneTNqt/Iy81LydP1K12s8XrDryR80xISsWUpidi2koRtX0PCft9I3u3YQiJ2bSOvD+whRw8fIsePHydnz54l586dI8HBweRm8EUSeeYkeXzlEnlx9w65e/cuefjwIXn+5Im7Zv/pwT3y8fFD8vHpE/L56WN3rjw8PJy8efPGi0E+fiRfv0b9iN/fHP8Cp8xpYHEcZxVu/v0UjrnspFi9uohLjb6fbpAJZ70Hx2X6BiRKpM0UgPSZ0mbKxD4y6d7TTfxxIiBTktzZs2fLEBCQKZM37hP/FKky4UvWCxvWN0yMv9Kn8G+G0/n8cSFVKv+sj54+nZgQf6VI4c8W1mPiPA7/xF2HDauRIIX7d+wWZFLMqJnKrNNaNs2VIGousxDJ755Pq+h5Hz8NaZU3Zxr3fFwSJ3ZqxS5btmypYjcjnt9rXccuayup/WOSGHqpsux0qSLtb+PCL8XYVzkmKdEzqF2VssVweGo+jHh+vqabLCfpM6Vfr+5ttmxeN6FYsTsRESF1y1atWrVsKbJp3vyZo7vvi3h+d+rG55GRobWr1MP5JiCJK5cu6jfiVWTE84jIyMhLxdoN6FS1LOo178jO1UunrwiPZMfLLhUH4HwV1j5HThzcs3r2rFuvIl9c7FxxwCCcd9vtRPC5M4d2L54xomvHju0GDRo0oF1vb0NvvXH13KkDa5cuGjdq/FAk7+k9TUjwJVw5tGft8l/HjRrSbrLvNCvDd8voftHOuqXs3LFj8eKt374zG/oKFv0eJDsMhPsuSPg+EPN9hL1AnsnfhbQYUWliRd0Tz72f5fMZZJ2CoLM4xpbXA9zUUXw7Km59+zvq+67CqcgexK/tckayx85BNoNnn8/nT64U8CcHEKvYuu8Byd+NWScUf3ft95iajlyGXOIzk2tSBnIe8ekKYtI5O+M37rzPDABnzkZWVbIQdyyyt+r3uHMbcecuuDCLOaeK5yInyrL13ELkbCWJnALPvV1CJhfLqO7a7ekqGjmLeHGuCr5X10kw4osbSxBzbtSwyTXEkJv1EFcQR1is2IFYsbN9PTK/VxeyqAdiQp/u5Cb47R3w0Kt1Krrck8WAu/D/t1oFkjvtapDzHeuQ653rkpAmRcnjZl7//rJ1afKsQ0US0rwWedy0OnnUojZ53LkGOQvOeLp7J3JwQC9ww5bkJbjiM/jxBz07kifdW5MnvduRZwO6k1+HDST3R/cgj0d1Ic/hl0NHDiRP2DrmGHyf1JcsHz2ErF26lBycNJbcnjaCXJ46ijyZCL87dRB5Di73cN548nrGYPJ67kgStmAcubRwLnm4cDJ5/usk8uS3aeTBwjnk5YrZJPK3SeQ1/OrrdQvI87ULXe72ZuViErl2BXm5YTG422+uH31/cC85cOAAOX/oIIm8cM71jx/v3yXh8I0RUX7w0+sI8v79+3/lB//v8f/vI1ocixaNCJEzZsySJWM2LeqrH/uKE37p3a+J/RA5kidP7u/nx37gIU1iP78knn6N4+EjkUqaxUyUOHGiXM3rxUuMzzgkQ8xEOOwmejz2GYPESpQ2W468ZQcPrJQ7W9akMUnsfIUK5c2bs+bggYF5CxUKqFWseBGjWqCVZ8DQdoV5Pi9pWrty0Z5D+7cbOrxTYYnPD9Lfok71QcOHDx9W3inBK4S079y2YY3ufXuUc0qV4Jl+HXt3bVOnaoUypUuZXv2D+nTr0rpB1QpFvlWwV8eW9aNWWr+iCcLY/CebE3X5LfnR1ZLvf7Nrg5BmH9LexT3vPd55ze/7bwLc5INyfivpf/JgWrCde+xpSfZ6VNb67BWiAZDsURIQdY5dYz/PwR79ZfdE9/z/Jw+fzmwzINMpN/G+OZUti7CoXKtw4tjtiqaIy34nC0GdNCTen/1koZlFc/YzoOwn7jMQd5aaMOTyf6IurAxWFvvJk1wQq1rq+G3XFUq145iW5uE5K/27C3aGj9eLZabXi2f5JsFOxk/n7fTvjqtpn2wq7He0Sur4w3BvU+Ktj0O8dWH9Ei+qjP83DsaHWVvlquQXv/52PvWx00b6iCtFM9NrkBvQ+WZxSInMFNyP3i75Xdh3dp5dZ+lY+nNmunc7hdQXa/onGEm8foLNcrB6sJ+T
*/