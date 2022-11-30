//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_AUTO_NOV_29_2009_0339PM)
#define BOOST_SPIRIT_KARMA_AUTO_NOV_29_2009_0339PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/assert_msg.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/auto/create_generator.hpp>
#include <boost/mpl/bool.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::auto_>     // enables auto_
      : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain                   // enables auto_(...)
      , terminal_ex<tag::auto_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <>                                         // enables auto_(f)
    struct use_lazy_terminal<
        karma::domain, tag::auto_, 1   /*arity*/
    > : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::auto_;
#endif
    using spirit::auto_type;

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct auto_generator
      : generator<auto_generator<Modifiers> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef spirit::basic_hold_any<char> type;
        };

        auto_generator(Modifiers const& modifiers)
          : modifiers_(modifiers) {}

        // auto_generator has an attached attribute
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const& attr) const
        {
            return compile<karma::domain>(create_generator<Attribute>(), modifiers_)
                      .generate(sink, context, d, attr);
        }

        // this auto_generator has no attribute attached, it needs to have been
        // initialized from a value/variable
        template <typename OutputIterator, typename Context
          , typename Delimiter>
        static bool
        generate(OutputIterator&, Context&, Delimiter const&, unused_type)
        {
            // It is not possible (doesn't make sense) to use auto_ generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator, auto_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("auto_");
        }

        Modifiers modifiers_;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Modifiers>
    struct lit_auto_generator
      : generator<lit_auto_generator<T, Modifiers> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef unused_type type;
        };

        lit_auto_generator(typename add_reference<T>::type t, Modifiers const& modifiers)
          : t_(t)
          , generator_(compile<karma::domain>(create_generator<T>(), modifiers))
        {}

        // auto_generator has an attached attribute
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const&) const
        {
            return generator_.generate(sink, context, d, t_);
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("auto_");
        }

        typedef typename spirit::result_of::create_generator<T>::type
            generator_type;

        typedef typename spirit::result_of::compile<
            karma::domain, generator_type, Modifiers>::type generator_impl_type;

        T t_;
        generator_impl_type generator_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(lit_auto_generator& operator= (lit_auto_generator const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // auto_
    template <typename Modifiers>
    struct make_primitive<tag::auto_, Modifiers>
    {
        typedef auto_generator<Modifiers> result_type;

        result_type operator()(unused_type, Modifiers const& modifiers) const
        {
            return result_type(modifiers);
        }
    };

    // auto_(...)
    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::auto_, fusion::vector1<A0> >, Modifiers>
    {
        typedef typename add_const<A0>::type const_attribute;

        typedef lit_auto_generator<const_attribute, Modifiers> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Modifiers const& modifiers) const
        {
            return result_type(fusion::at_c<0>(term.args), modifiers);
        }
    };

}}}

#endif

/* auto.hpp
9QS1e62KPZ8segmeT6zynvOi+MjmwwK9Y2e14xWPvci/6Ml5nafegKsn4kDdVQ9Y0LfqKkEpKpGCEizoPKN6bTLOVhV1Gnn9ixY82XlmwXx3VVmSVuXY6UWWqmbbQLz38Eu8Rcc8tiav/Xhy1/ahzqaqxv1iVX0K+8HSapULG0VTof3D5o69yfelNt1pbxqUMWKY80SV+CWl0Wqj1uMNxxsq0EJ3bZBqisvuCSCPe9KL8quEM5+qPp6e6RNrCbIcO9uPe1IplmJssZiqT23iLo6sPO6xD2x37KT4fArlbMUyZiDA0FiSuA5aaKOy5cVF9O1zp3+RY+eReY5X3s866HilyvL2k/5FCzuhhVD1OfX+CEX4F80vcOzsotyxMUSyzu6qz/A1sIvqtVMYD9crBy1VGH4jrsYQl3P1jV8c96Q1vPth8/HGRoGhSWqqwqd8bW2sOp68PjjM2bS/cX/DBzJ4yPHG4x5n0622E++c2N/ksUVvbHz7eHLljqEy1TEq6wOkG0gD2kiPxxm9tPHtpkHNxISijOONiHXKMo4nb6TiT3wc/RuG/7jHFpeFNCavJlhq9Dhl6zr2TlMGNo1dgbASZ3R44xcNjWjPNMXWlIzQqDjeQKmPJx+mlsguTFMcjR57A7f0VAO1dERj8jJKKnsyTbGjTkrRWGKLjjmevBhRR2TUYJmxcf+Jj0+8E63ijlBSm4QasehIiik+hjSCoTZnY2XjFx+0IveM+0Zwt/F/SRf/tre+SoAlAfN4Qpfuszfub0quQIv3RzOoCBEroh9VWeiMOhorG95urDpx4MRHjfuPlzibKok4aLqVikyjwWpKXkdtPn5zJtd1cyYBahoBmriAyFqqlJJSou9HJ3F0l4xuGvvDZRwn+vN4MnpbhHkVd72bYjpOdNPO9ob9gPJf0DeBU5O3fWA7vvPl90CY5DCmMJ+KKkgcl3QeF2MMM2QGrVZraK39/ug0VmJ8Uk6801QVTe8zLo2FqX3HpbEkFeNCE5baWJLO47Ke4aSn0dPTSF1q9KTSH2ujJ72RevY0euaxUQZKQS2gRFrD95MtiSdrGoviKCUhrcYSOyDme6nzKPXDXhTH/+83MNQB/js/PiS4b+KhZVgLTxq1Va22Y/jaLwe66RThAZURHE12YRfFESps+Jr+nvim8Z3jhe0SPJPvsza+HU2iITCWpLWxKuo4K67xQGwdWxsrKaAKKxOgbT3eGB1y/IPYEiG8R4n3a9SbqobqxkoDe9KUH3c2/qPxH7GBH60ReDQeP3b8A/oPi+GL49QV+/G01qdp8k7QYpRIgGqklATYe0+0NFaf+Lpxf3QozVl1w8dU/icUVnniZOOB4wR6XY17Y4UPohI/oKVwa/uJrwhbVB1vo+KOIWYwQKa96dauE1+doE5S3Z6uEx+dONWUPO4INiz78VHHzU2TgKSOD+lFCgPkqjo+Kpp0vCF+hRoqIW1TwHVckoQrnZagxW+ZC9awKBIwmXFkA1tJ0uGS+G0X7qi3IXknCMRgj8lR/h/mibUzjlfOZO/3236u1fDRjxq0ydOfi+/r1I8BDdmKhjmJSGw6pe17Muttrf3dM9qJzmOqt0v1OrGUWz4IpqolqcdL6o976ptubTle0oTta1BaGfWkpE46LacdsFqFd7RUCQvHS/a69zke2Y84ApxXCCJPHvOcbPLsBSKvk/BgdoRhFPF4Q36TUpffNGgj1ncJbVbtWNffOPuZmrxN8+Y1eVqaSlrkcI2kyPx8RNcnREctx5GmXqZJpnZGp8YTvvzfy1mTWE4/KocmohE6CB6n7Xia7rG5FJtj7ZW0IU53n3CsHYoDIdoKS7pu0w4/XHsbbXS0Fipbkyo/T6oUSWG97BeaQqtrPy+PdzAavE7ksOTSn+OWhgOiri7FtDrXTO/viEp6b6xcndI0UOzgYP24xUA9m/k7KVRtC+2z3qTslRAdCnaZFs4P9NeJO/3TMpCLnjaWzyfAT1oRs5IdRN0utmqeDP46Ql8+K6g5b3povzW/L4Fd5DfNJtp292YYkqFt339jhRscyfNHINmFSxOo7dxpxo2/LezW1SbduhJR/KmrZHfg35pnm+bdqhHX1yJ9hTT71JJ2FefC3+p6ERRrNkCBkBhEnGEAEizt05ezC2TPVqKexG2h4N/hw1gZWdWcRDzBbl1pFxN24YqvvbXDBCWMSvGynbiLqZAaF6glPfpRHwIPDIWugE2bdMdGWJvYS2StxwYfENs512Gh2KXA2cwZDos/cQbiMer190szTHWmggLKpnWxxZ6t+KjXh5dSJe7uAFQu6uHFyMYlQ8fG0w4TosPhxevAkryVNui7hCqt1ykno1dp7zLh8xXRPrTVDHxfU1qqWp3Ash/ZBr7r/mZJmmZzvxMYsBILQ1dtUSKTKe8sRVDDIGZ6gNomDRpVintgqImG7My78sgdEwsugY8NQL+CXfjTkgRR/LiKBZiwbw8TodioljSxIMeelWvVymxZV7MlNY+cHJucnGAbHCT/5CTwRwvwB7xNgQ41vEl668SVA6kV062G/04p9o4J7uvErCEYyxY4sB6O8YeB0xE0vZTDSL2LRzh/NoyYEMeGcZUWxQ8Tj0Zc9CveNtCAVc1p4f1lg4l07J8Uett6nVpoU75GaVdoniYqpiCWSWmnucsv0hdb9aOhoDAF7DxvRv1scglcoRzEOvETaqDYfbh3BGlpZHmIM03N8jizvHaLZ5zFOy4UnGAqKAr0zyEmJMubHk2hvxZvOrN4mZGJq/UrxGH43i0Zr6bgPmGZY+fg2/dbwBhguyWyNfSRxfI28w1VXUkqccDMHqQ7dhaZbz9iiXEQRPpyQk4zTqYZ59iZm3R7pcWx872E6DgXMS6Bi0jnFzUFdPF4g3RhkEylZV2gjSrSJhCXbSVsrc21azm2rH01nh4CNLOu9GR9UODTptnBeDuzaujVluWBR0ic/aeKyy4/o8duu+VVqICiVw6CJUlbpJ1Sg9sc5dW45eKhUbNnH1PhaMOxdhuCqDTi+ZSt7m8ca5+BP4apPUtGOm0PDAGQ6Uut4l/ZZ/TWMGKCmXpgEIosAyKBaQiA+fu2LvbFjFPqhKOVGIxVis8Hs2BvcGxdzHd06dE9xA7WeJqkr2pB+QERUgBsHBk1ifAQzjg8wn5MTEZyceVXnXr0b7rSTEtafD0Exv6oN49XqZ7t7gNKsnAEIeIQqme3RGIVtM9WiP5fYZHsJo5zm6ukPfCyDwhBwvxMa0LLGaNIlEpJRBEjF4lPNE86bDSdx/SUY+dhiRcIhAa+g0n+t20gUVsEdMLxyj6M77dAj1PL2Y5e/R6dl2YG+7BJK5sHcCDOM6vKJ67/inCq25MRnEN4nUGNywd1h+isWPQkI9rJOCkWbTeiHWsWU31RZ3aluyTd8VglTHksYHKCMP3djp2DfquMBK8bsU7zW8CmqUqbex8gmBbwoDspMgbl8RTaQUqQpNU6dg6/g+IlrxyxXkux8zu73fsIxPdR+kEmZjdjpKi3rbXJJMFFufgYeJa0pkF5oDbmZOIBi1rA8wFFfb0VeF47wF3eT+Wr3gau6AA8D3kzua+N/kW6kpbVUEBoTj9qgUfFsmRVORwdzBEFHMY31TO5Cw1ZJQ29MQ0ydUti6gYqybGzJDOrpK03kMajzKrtiw5MCKL+tMT6GOvgYX4h7KeaQ552q+6td4TBCmnBbZqyNfsYQVTvxgQgkvAEnGcA0naCQ4s214oE4icOIOHdEvGdBezXfyElhVg4F9r5fFD85QChwwyT/46K7Vjol9MnRCSphA5Vz5bwfsfa3+PapZfwow1fIXzlWbOPRQqbWQrTItXTNPNs3eeLbSbsBLTksFpSr5Y00OajD5/BF/JlDNEVbBjHUT4pibGGFkwlxJEVtEe8j4kjVmx1W2j5/BgaeEx8PEDK4XH/Ti3ZVuPZig7KXMXfW/1bxUODZPoXzLhavk1X1ovkwQmLfTUv9gvvhQJVBbVxDS3zNWpwnTj/P1jp60BC3G6G3L7CUf5LMwRmynpjxXOlP7Loi3nJr5cz5SpJc5SHIavpdqwBVDORrXrq3g3WaTW0zlVlb2fJ3shNZtVDi79SLdnuKqlbfl1klq56N2mFtZp3u+Ud1bvbXRu8yFK4yX04eL5WslvzVkTsT2qjVHotqYik/kE7Rx2leXerA7KP6Z7tlEn3bnJ768re1Lx7zd5a3VupbIou1GpYZ2JZEeVXvbWRm3Sq3vHKQWpBjuqhyuvc35RdglqTqFi2BVJnqdI9dRFrSEtTz6GaaW9W01xK3fKm7GMW715tH5FrZg9XUCmHJQ6564u/D7er+0wuTcnddsDuuhjsboWzNDmz4pFoDHQfE7/uT9t4//0p7AJ7TkUr4HZwLcEtQRHuXMCdbHBbWKdNCeBV4swqsRGcho/RppR09qa0xCpyLsOmlCRJnDnQns79MRLndpv01BWjKJpsWEWtN6DYW9tooQmGw1xrccHZQChE0sDYFiTkquTEYvvntAX9lYnQw+J3A+P2ZmkLgtMA6P8sAVxi+9lLq2ovbL899DngEv4mXw0F2028BcXIrtwYudUHEgu00Yn01nv/uw2INhnK/SwwtkqUEkEp04Zrv4NQ1NPEGxE2IZOb6Jvyo0wnbsmPeCvyYZPeJ3Z/qeuNX0Bow7KaLVJWsxHMlkJLC/uJVqvcT0yJpJ4cO09lScC01KjKbrmn7NaqGBN3cTLsKglpmmWaZiIcMyR9bWgDWapim4q3mZDp2Xh3N79EL/yRTSWf5sXYVBJwc5MjPBhMH8F3rhxeYzyLmfCNATgN7vY49NCsPtkfgF0bA+w+079DxCC7TkRSJFJO20fAbchaz7LNk4bzDm86fCt7mlVvvbtKmeCDuea/DkAdgtoFH6m8zKC3QlE1npb1qOkGqqkVTptpNzUVFO9CYNnvQEZEFJs0gOJftDlwjqTsFtBUZz7ZeSbfAotvXarHHqUYZ5bHNk/GEOPTbAEne5J4LLRgvNECTwP1O+Jt69MIWoDinc9gj2ecqezusytdEEinPUeronqpVCp/HNWchcMq1ZtK9XqdiCMCvD4hrk31omSxvf//od7Zn4GIyyTyPtS1yPGImznNZs1bH7r1MK3beoLkuqo765w4Zrit6s4TgDBCiVV31lKQt4mCmqiblZ0lUkaWQii4xtOcw0tgL8FdLTWK1o+3jhgYgsPCJscrhYctALITCLG8U9WVUnUqJUHGRpjY4q2nVw7eP7CKpzBqg9fehJHZrCmHA1kYmXezCu20L592vHKmSk/JqsmFMOc0Xg/R5GRVwdFrZXSs3KeJV3hlH9VJs5NLGJ3qsHhtOIP1nsyqJc5qxH8drUy4s/VUmj17Nc9u3dts9tSHgs0mopAcj0CbaOF8w0DfK0/jXCXT5J9bkZ5O8PXw2ynw8EikgWJzjU7960incqGujCOuSVcy5CkeW65Bx0TGd7re+j+QHwS30jdh+83iD59gaVVkKdu04Pas4FYAebDeUX4/JSOWovweJPfuFtt60MK2/0Ih7BZVSXLHz2YKIcYeyFxFxd/nD25Nlum/wooHO1ApPk5OoBAEUwimu2KYuN4nLJ8wqwzaYJcJtEG7o/xvJqYNKiUqjngIUOr4rMlD3Oo4zVNPo6F6NtGA0ATQmMAruJKmljxFI6OWbIRZn6d4OOqg4LVZmoPxNBCA1bury4YSKlrZn4UMVdY8mnPlC9mj+D5byWpt9UzjbE3Ya0XfvbZSpCRLZj1GJ/JeK8nEMS0xjLRbdJtpr1WrCB1lGvdibsJU26pg4ytNK0zXGtWnYe0O7NDbjIpWizEpKHuNNt/KW+w9cfhaXeNZzaio8mNCRWPZHmBGtp51yFFuog//zxdkHXSUf0koCn8/Mv4eMf4e5y16nXj1dCekEGqwx7gE3Xfu14l/mHijHSI7sU5cQZ1ofZ1y72GdwuAWVdkkkZyxXgqsvnz97r4gsUnMtshiKDV9sladjdod3cJWqx8T1Zau2G1r1bPGfYjgo/m3nbrfhjqrKFJa+aNNK3m7xBXHsKZQb37ToLkEFfkU1jRpC0SdtCFu6EkxfeDdK1ZVpBhUi9ZepLL5QHHPxymmbFzptzS4O8v6a/s6Cf9vj1rUIBF4u2keHDurCFfVEa6qs92mFh6kl4M21bu16s6tTrVwW9Wd2wgGN3aWbMzeD4EUIbEgkX271cdhV7DGUxnHZoUHCXtVMPYCPqu0EDlQuA1hhEdWew9Q+NZ4+AGJv4haIHTTSziwW7bRoONrIvbzGRNtZyy0HVBNW9Zw6anPXONZwfCw7d80rr8GKoYWpqUd7Nf7WYflYFneZUWVtohnBfFzmGGVeA9FiA2g1dr9VuYplMf04fW05oow+uV8va1PFV6qQuPBxIB59lrYoqLFs1H3VBDFaukOBStNGBEahEdg9ELfgdlj+EE9ifDyOCBem51IATxGECT3/7vji25NLw3wmHicgLDGswkQ2PoXQn7FxX6zb3bUWVxcHO3ER9RCr7N9hnEv2LbWDmwWz5ym2U/fw/SAf3nFQ1h9F7yJ1ZeplaRBuuYZB6nMXtVTj+uyD+COGladYTTdEb4Tdh49To3arRCbZc+qyj5CpBsuHUxQlW2Ox95WC9u0wnr34cAd1Ce1cAu9zXV5RKBAKxSua62BG1yetoA16wAtNK/TR72pt3xTRMjGnq/dZBV/bNVxygtbZm2BpKz3IKPzphYRvS8s1QU+pJkt7qZErR9D88mzJZAsKm6H5r6AEoprmlX5EmT9Bx2dkP38IOX9mPiqpzOB8n5M/PI73IBq/QNkSbdWEDW1nfF7YRMVEbFnW97Ln20gedV7mOAlvq63i/t06QkkwuAYyyrGf0gwuFFXKsCKfKbHPXepnhXSeVcuL+Zm1VOuwRDd6oiHgNFT7hOnTwD/raZWbw0FG0yB5xO5Q1v2EVchBqaaBiJBMT1GnANuaG9onj07zigSUgS5k/5kZzfxnuBb2CZMYRPtHNSAzpJNRLDgmMWzjgA2qzZUSwziVrWwJWtfpMisHczyNmnVWZ4mtbA2knquWlipMqwTklJLtkRTNP5idk5V2iWScrcHpxALAvOmyniLp6UA9vkh6G6XAEnbCm/b/yCiWCd639Pu5nzL39GwWxNaq1QpzNMSvJKLqaVi8qiQ3REWfbX3KWRFbyGeluWH+pZQG5xEJXDd4wuk7J/2qT75cxLy1y5/N5a/ifPXBV0/0JHvtaGntbeMuuX/jJWxyUw0D7Xe06J51pk9Wwkz6N463bvFEf4HhDLe+HQeIEDTJmG6eCbl9PFMYmFg630/FKw3BYgzOAyYvMEsKa0ATzCRD98wFVOPQAK4Jd9JmuYmvh7beXiMBwbpvgcohuh7PQoXpsC8WMlUa2/hwiee4MKFUfgoLtwGKwgSEh+wuk8ZVrQfiFWQSjwilZOfz8VrnhW92Gu9ONqDazirY+RCn4XzzbFe3vzAKfaYJYreIIw1HqThDmCs31WANGwCu+coZ4FS0Aa5T4k9q7NIDbarJXaxrinFJI8Ns6p9xNyIB5pgSiJ7P3zQf6Ukq96W6ODsI+6vHM+8HZkzVCd4d3mbES6iDpoVIr1jEcLltSk2d5WjfGwSIz/w0p5U
*/