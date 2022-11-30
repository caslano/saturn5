/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_COMPOSITE_HPP)
#define BOOST_SPIRIT_COMPOSITE_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/compressed_pair.hpp>
#include <boost/spirit/home/classic/namespace.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  unary class.
    //
    //      Composite class composed of a single subject. This template class
    //      is parameterized by the subject type S and a base class to
    //      inherit from, BaseT. The unary class is meant to be a base class
    //      to inherit from. The inheritance structure, given the BaseT
    //      template parameter places the unary class in the middle of a
    //      linear, single parent hierarchy. For instance, given a class S
    //      and a base class B, a class D can derive from unary:
    //
    //          struct D : public unary<S, B> {...};
    //
    //      The inheritance structure is thus:
    //
    //            B
    //            |
    //          unary (has S)
    //            |
    //            D
    //
    //      The subject can be accessed from the derived class D as:
    //      this->subject();
    //
    //      Typically, the subject S is specified as typename S::embed_t.
    //      embed_t specifies how the subject is embedded in the composite
    //      (See parser.hpp for details).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename S, typename BaseT>
    class unary : public BaseT
    {
    public:

        typedef BaseT                                           base_t;
        typedef typename boost::call_traits<S>::param_type      param_t;
        typedef typename boost::call_traits<S>::const_reference return_t;
        typedef S                                               subject_t;
        typedef typename S::embed_t                             subject_embed_t;

        unary(param_t subj_)
        : base_t(), subj(subj_) {}

        unary(BaseT const& base, param_t subj_)
        : base_t(base), subj(subj_) {}

        return_t
        subject() const
        { return subj; }

    private:

        subject_embed_t subj;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  binary class.
    //
    //      Composite class composed of a pair (left and right). This
    //      template class is parameterized by the left and right subject
    //      types A and B and a base class to inherit from, BaseT. The binary
    //      class is meant to be a base class to inherit from. The
    //      inheritance structure, given the BaseT template parameter places
    //      the binary class in the middle of a linear, single parent
    //      hierarchy. For instance, given classes X and Y and a base class
    //      B, a class D can derive from binary:
    //
    //          struct D : public binary<X, Y, B> {...};
    //
    //      The inheritance structure is thus:
    //
    //            B
    //            |
    //          binary (has X and Y)
    //            |
    //            D
    //
    //      The left and right subjects can be accessed from the derived
    //      class D as: this->left(); and this->right();
    //
    //      Typically, the pairs X and Y are specified as typename X::embed_t
    //      and typename Y::embed_t. embed_t specifies how the subject is
    //      embedded in the composite (See parser.hpp for details).
    //
    ///////////////////////////////////////////////////////////////////////////////
    template <typename A, typename B, typename BaseT>
    class binary : public BaseT
    {
    public:

        typedef BaseT                                           base_t;
        typedef typename boost::call_traits<A>::param_type      left_param_t;
        typedef typename boost::call_traits<A>::const_reference left_return_t;
        typedef typename boost::call_traits<B>::param_type      right_param_t;
        typedef typename boost::call_traits<B>::const_reference right_return_t;
        typedef A                                               left_t;
        typedef typename A::embed_t                             left_embed_t;
        typedef B                                               right_t;
        typedef typename B::embed_t                             right_embed_t;

        binary(left_param_t a, right_param_t b)
        : base_t(), subj(a, b) {}

        left_return_t
        left() const
        { return subj.first(); }

        right_return_t
        right() const
        { return subj.second(); }

    private:

        boost::compressed_pair<left_embed_t, right_embed_t> subj;
    };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* composite.hpp
Xq3qFvNkwbw2pF2rXaW+HNNaB1B7/MHWZT9v/wYMAlKd2zoLnbuyZ1nQjgWbLUueaLN+tT96RL+qsLHwULp1auL6sLOcKzoqfZDqqKKddkUoQKwYIP3clwD4LTiVdJrIUxV9ssmrPPmYyn0QoblqWAgwm/yYraDkTI3x4tyQUb8VhgHJpfPFAexLwRGeVB4V/+Jqb/3/4GSHsgT7CwY+3gx86T7XazI15TSfCCH54Itn4b9JpLmeKY8LPuGcf1mx6yodpoit4HPE2E35gg9YGe+gd8BZpmMQ5KtW+YEXGmwukXIXv1q47HfcDlZtqBL+XfjV+/sXL2KLCKIOVVWhSuKBdqG7qvXmLgyCHHzVR5bRBXfp5n/1mu1z+4OLqFGDI2J13Nj1l602bOCbbNBcv5HPc/l8nd02tT1bjxjDhA8it/XpTZ5/B5Rz+hB2c41kgiRkGotrEi5j8UL/DlhCU4934JuwCV68KOI16Kvqe/wlzpxGCFM/gRTc+ul0Xtr6yOPiu9jUTlEneFntK+Amwausxc+RBfWB/qnVelZMZtCtWytO+wXvlAbw3uvQdfCrMWg64q+fUBVu2WJXtKX0BgEBfYsRY71IDJoP4QoTdKy+jCjIUG3TtTMeX5F2neS0VbgRJ6QPOPv7l1YjtTnMkIBk/EsfwszjEk8eoWv9i/6lD+gP+N9A9brH/8Ya+huZ6X8drdA/73+drcnui+9Ac1Lp2nyCm3trlrjb2MFt5GsmKlVJXzcQgIT1QcLjXFc83nBZ5Ziv38wQg19baX9SGm8wsFHr+lPrvHWb0Ow3+JX69Xy+m8/Z1+KuK7fF61HQiKNI4MInGUElb35sU/zXX4GVU4P1ZsoICnX9Ya/8IT/GhWI2m3hRYFCJI20VohHtifEWsMVOsNPfFiZYlneKAieL9NQ1XtGD+u5/v5tfSg+t3fzfZ/ZMgKXhKW7rH96ippuP2E1HMXtL/w9W42XbI2lNx7a+Jgu0tgJ+gSfMqbWpTZECLmXdOyMDvm7T3A5IFauhnytLc1MMnik0E8sRFZoBZLZ/6Sy9nHkBSc+YdxKpLxy/XNApYuhxfJrTiexSwTN+Bgv9HkTMY1fFZpH8vDKYDZ5J5AvtjEvr+DePhd7m2oWPuLinhi6NYIfVonK0aHqfFVzkf53X4ni1EJVln9ZBjF9qIRL35KLFx+rIWBv9NsWwEjDRhQSmsTjA3EzNoz5c4Tz1oSNJJEX067GXWSy8N4WNxylIxjJDeyOjZOvgtGiDYN7KreqwlzQBzInp5xURGSO3UVlz8ULhMxdHkJlucY1QsYTVK2wCxvtPifnPA6yISjCQyn+9xA25To2MPlxMHU/CVH95KMExvrIM3jxC5CKuDAsS9du1qv0vwXX9BCVjPHNEyx7JsMCdPVXfjh0yjadRaosRZxzzNHA9IZPvMnYeCOy8L1Ic2Bu5119eHRkq3x/ETlHQfT6FfESJEoVGAnt1r3yDH+IRJkvEeVjYNTAxws/TQLSK75q7eMSdTKsY15Boz0Bwq3/qLH1UmepKvH7TZSgLD0uzE4wGMBSwfHs9OC9kHWlEwt29tUOFwEL+6iGXq9k1NdcINiaG+RltIWYK5hm2H06tMfY682578lcAR4piZt4ifqutTmbfwLzx0DH/9vgQxGIYVVCcV8BpHtN2IA8kMveMWsHY3k4RBp9MEg22WB1g5I68oDEGCYfojAyxR4CJOI3AaCxJVgQUUXsgs49XC88eQNdB+hRJOAWMrKp9KyAAN1PZeLCRHQS5HKSngMrsFrYW1Jf6rKVZIpZGDQlcL5x0HbIQXouN8GJfa82wRl0+8AjLDcR2FTRb90jykZq6zZ7CpxVgmalebbd6NbYP6qw/iS+npXv01iNkIMkChw0eCNn7IkP87TTXz7/Adr45/kX5Ea9oltqPEDVx5d+gpMROZ+xvrtjBweo9FqG2Q4bZgsw42+0kzlZ7IaNsD6mxLuxWc2Ls2sS/WDRSUGfi9dtQVoktu3AOyYV7oqgiv24xSl+gF9LxRwsgkTkk5Dxh9shgVkkwh0RMi2D2SLEugtkjxcDIe77GrCl9d2VDBrRa/pWN9LcWRuT7G8Y+lgwe/J2F0Odo2beGsoWBc6cKMGzbdF7hFluFvXcpbx/QbYYdFlhmp+f3w1XSB3LmuNjr22GoECmhB8pTs5f+W54XTAXFGvpogViPTwe75O/6fzzgqvKnxD5Q0p/ygTvgI2CFdihTTQtjOwgO5Nkh5Bjj+K2rqDpzRzX66DN3IPIaNSQteWAvVw18zxt2VoWWv1Y2xEPi5tcuo/ebHKwdYtdMyzcBJlwrJZThTqX7LGzkoeN7nziGqV3OiYDVciMozfewg1fJf5ZAC7siArkJYxXC8kmNFFtlVnQE9i7PCuxblmEQBvXQST+64TLKPcJFF9n+qR66woPlV9H5skEcqy6TnifoDb7I8g+M9ksM8Jd7lmdSFYbLGtXCxrnSPTbN96IMAysqssVVLNg+3INdWl+lGFslajzimOudgqOBs9H+hs/aXUHRmZ6CdwIf0mDWDjBCHsvPufBtf0VO5Bp/RS92t1zH6Uki21/RE+knQp6C44YPrsC2wxH2/Q/51zK45vvXAnwjmXJ6Ni3U72ELgmfERyeGLzFbPdf7sTVd4v5wDodUkWIavD6z2f3lVZQwh82iIYTbSjiXZt0c1nAcTna94q5qnLxr6j2IBMOuYB7o5Wmek54P8VU7qYqQfKXlQxPGVAPuTfok56TNbZW4KL/yQJcZO6xiLu1vh3NbZTVJTo6q+K9QR6VsRx1ZhST0Rr7oL82PPFC9IgPJD3KpUB8XJ3tfVgyGlrUjVF4lf/A4vTsYEM6XQl26rMtl6tJtXX6NLqun0UIXx+TxDQhpOh/zjMVz/WfSI/zCBfkD5c4of/LOJWuvGLAfdoYdHMW19z2OQ5rtOFINMtHwM8i6s6uxaVQej3Miq6G+82Z5nJNaFXaH4sHNkFWdkfPYWqP27/Tr27BfsdWoR3Y0Zh0X5ycTixp6hxX9XrEdVs4nsQuFK4EL811oD4nvN2WdJ9EXqYBEDDGYId355LOZQBscN4A5VLabnTlW5Z0SMSxIWl/9Gs5wCIKQXEjNtQqNNnc8iBUnxtCvFVuSvxvfUeRmAc1KaeViijuWN8fiosNll47vyFXltog38B5MANaNpsfxHS2udDHp+iRThWK2fDYGFb6hPghcmJaem7VQ+91wOQ8TAqPZ2FEHVNZs7lhBf1N4TFVoPoX98QmNS4ZbVkGNS7JhFdS4JDPsmo2twXgcrhVlIetL4Uz1ZqFpvIEHKuOSfHtBjymn8WerqqxP+tQnLR6zz0dZ4OMOmLt4oHjDYrS5qyh5MdbcxTN2TD7kPo98FawrvnvxeUsxwCA0avB5U9Y/ovYl3wOInX9YgVhwqxw1iN7TGgm2GG56Db3R0A8YerOhH1Ggw+QUz9Ll9ll4YKtC2f7o8BZ5pj/2u06IYIu4CwSdJFQSz1hL+S5+8b0jbpQ5I4Jt9lOC2HcFEtLthngUW6gmAAripIEYvVjGczqK8dRuIVDK1cyFaHVTeSrIw9enKHKLbJX7PNZw0LmRTWPx+MP2/pL4DpBYrCO7qtAMvBcZS2gq0JR0RRHB3IKgL+yqqioTwZyCYHbZTDjB6Nm2I0rE/xqj04Xllf7XmumDkcFCyxF6boGWXaD7ErliZSta/Mpp+i1YCagteOUE/VZVhuLP7AbV1LrAKk/5nuV0U8X/gDoOW6jj5u0XTavUw8svmvPnLkiSU2XYnY5nMu75yIztGe8G5LC/c2RmbA9WoSNyP5WLP4uVR2XLzff8q2bReeRORDIw1Hn/euS9UZHhw85yQlHGKng4K0TFGOvAuzTvzwLIy5PLr1gNCtdZl1Zn3b+rc8XH64zteQCt1MeIknzOP6f1wGaoaRVug9Q1aZ0+/tMFvkeuLrhszrGCvXLUANRmWbFyVf49aDnxZ3u4azcRsl+FzofQAn5m8BPznWQb/HtWWK/UJV9Zk3xlBb9S1/cVIu+Nc5Xxs/igvjvymVhtviMyulJ+WM0B/iJXsZFVti1+QaMJOjDf3ARCYId4UjFO3eKDiRl097FhExGwYPEtn0bPI9fHpDtyTcI/0U03H71zYib9WTIg8yLMHHqcj90gmIpCp8jfGkL8WnU/NNOmdLDL6z5xKT1cdh8C28CEVFys1zyRSGUoSVK/dwghJ5iOhlJRT7QekcVU9WOUNGxWyRmPpkgpru9V1y77+nZ17bavr6dr0E9wSQvkH24BAU1a5/cB7Z5PEXMwEdMsrsXQw64KgB6p8K8ChEeCFkRrRSEFtqkJN9/DzzuxPQ/xUrhJ8JviqKF55MFFiKEOW3yOx253KsZT7YiMJNgNKZBNQYNVH1vRWjzdFa29Y/RHbKGMdkSmfRz4rgB/P7dMnyOeRcMCf4zMoDkbQy2rKu/brMTdCkoR1PNK6LyiTjYjAMuBFN7pTY1NfGDkCJ+DIFa/tQpcveJFfgfGzSfuYTMt+YtvdMFuyPw+MhsvSGTKv87sMplXCbsbJkSIiExZYFujnbsWnY2vBUIzor1NWQuJPZJv7CXE9SxwHlgVI2AsdRtLPcbSbDnpI84f30aP5As/OstWQnKMunkGN9ermy55tboJnkAup5vxtZ2qPrf84eEu03lThiODDhcdbjoy6ciiox8dHjr60zGAjoF0ZNMxiI7BdHjp8NExhI6r6BhKRw4dw+gYTsfVdOTSMYKOa+gYSUceHdfScR0d19ORT8cNdNxIx010jKLjZjpuoeNTdIym41Y6bqOjgI4xdHyajs/QcTsdY+m4g4476SikYxwdd9FxNx2fpWM8HX46PkdHgI4JdEyk4x467qWjiI5JdNxHRzEdk+nQ6CihYwodpXTcT8fn6ZhKxzQ6gnRMp2MGHSE6yuiYSUc5HbPoqKCjko4qOmbTMYeOL9Axl44H6JhHx3w6FtDxIB1fpONLdHyZjofoeJiOR+j4Ch3VdPwXHWE6vkrHQjq+RsfX6fgGHYvo+CYdj9KxmI4IHTodS+h4jI4aOh6n41t0LKVjGR1ROmrpWE7HSjqMPR7Gytn8yyHT9uTwL7P9e/L4N59/R9GvbOpleAJHKm8neJKvqhtjceM63NiibozDjUF0w9hTxK9P5t9S/p3Gv2v4dx3/ruffDfQbds+Ggm4VGBRj1SL+heCJQOF7gFeNtZv5dyv/QnI29jTwL5hpY20NV7WMX5zAv0dwf5XbjXAmHB3H2ANew9hTzUXH86+iaLP5dxb/PsAvP8i/wC6Ic4PhgjvCqlwACSz20/tEoaV3LFxi7BnN727nBqVInrFnNdcgDsrR88FIWjigeF7SfQJrXvC4hX0LCo5Z4fLlxdKzpuDxLTgmO/hijLr4Y6m9nuWgIySE8iqn+01c6Iy6+DVftKmLl/gNYBlmc3//rHI6hpVm3kemXDsv5TM7Ll2/klcuTorv9kBmELqHWNjYh059pCBppnrUCuylZpep8MXmzOr2s+CdNDCEhtZW2GhETyN/zHvetZABYIryJ/yNoTZvnJM3iy7weNkr/Y93eeu+T3eM6Bl/9HTES4SSt5aP8tbyGYT8s7Q1sJ1G/uXA66qeeKoevVU07W3LAHN7grjjI9hadfvPmapo9BERQzEXsdnDhcNqv4o5xu2PRc84IgOQTIfNmEcL7YgTGw+yEPra6Gnv+r1FyP0cPG31YQ1Cki8gEqz0PzeAAueSDHH5XNKWPI1XgAZnLcC4SmUqhH28//F8b91zjiSBDDsr5ctfIzrPBf0MUhGPgrmE14h2GNFOI9plRHuYC8iolCtQehVm2XqnpgsvgHZ8wguuSjmDXwBU9Xmh6JO/4K6U1+EFFtPnyxqSeZMZjnLQo1UYCWKm9OGggEGm4Os+i/zOnnbsSJcXHqqC96QR5Dg5e71rnwYQXPSuQbcDe9QkwnhDrOJJdDf4S7sic4ygzx/shTNzdpqeWvOpN6IPi7VcWs13GYeY7QjJ4fzlTte8Dr/Wg6zlPaxeGsgN8yn1cyMivfR61zdOgdu4asCar0IU1Dwi2LPAyIUL6Hywx/KrhNLg8KTif85xOao30jhJd/e5j/me53+I+J9fSIt5Jof0prIQOPgVFe2sGvqAhi8BC/x0DsRJWAywGCwnOc5bugFYgjWlqQeCGedhWcyl7nNB4YD9cRigKKmWOJfjxLkgVOcKknhiBzPkxP+BogFYERqJ20UM6APzPdDPOtCIK3ZwQECvW+4Sep2IAeMq8TDunuQ6aMSASa2S/WJ85YElDCTa6HojusGIboTTjSXqrk/TdhdmJd98LM7pcUOyNwSvnI0F2goR3BDjm54YZ8b2GPVYSS6+F9vrNuJjcMkpro36sfhVsRhexyKJ70LhpNp2/SerbTciM9B6o/4hrmMR/y7kX855zSofo76afzmVtrbBpW0Sr2MQVKgaTpFNDVZ7f51xt5djj24saDp+WRw2tNWGvk5+JqEs2P8KAA5uolrE8YIWf0VdNFdodXjxaVSDoEHGdyG+JjyuJiOGs9jrIEWwCeBLl1ZnxE5ziYJjhsCZiIF+lUa+XhoJlHrrVzJ6XUGVFh463jOpoNPgLMLUDL8AuUNoDnTXL0Dw9Aojjg4ngkJbLYIrCvYSXoyxHB0DVTUE5GvqBsirNUxc/lpB3RRchIu7tBV4k0sH18QZiISnsNvYBUsO/zcJc3/eCVsz1rTZILqmEHZ6qp74uFIRAzAQGuCXAk2R/rGDOVYNr7MsMsL/OssiQ/yvg+SiwABVgMDFEGAiaIANAQ6C3veFL8VjQFrIosXTH8MYlEa+WRq5jQbrFYzfQZ7JQvNCq1NbN8VghZD/dYyOiqeQmEBjU0CQjoowtbwG/Npq3ZO8y7/x7LFq1KgHgjkZbTXVB7BKlFuAPhSRcLhyIpSclj0xXgheVBVrXASL30VNgeM0TSJVsxoh10EMMVccXIOclFswlo54DIRdeGKPw+TqAOZ/KI0zBpj+YGHA1eepcSg0ltolGFRbBIMuwlcZMfB3rr1GLIe/iNaVGrtQeaSgNDKSBmp1RnKgeJiMN7AcEjdaIwO2JzGMQEKdKiwRd5c4tTXxHXwny8UTD00g82wxNrKidQmj5Cn/wLJNKiPVfGrrCAUz7EZykzCmIMylYFNb549jBCOFAMbvqnoxXK6D8Qk+NVI0X4Ge2kJ0Epf2hCVu8Mcxz5ERrk57CtUQGzvUzFHd6GLks5yIO73tqkc0FVlovyHQE/RiZXufXhyWn/07b99NJEk6hlWs1KpEU8ThkFUVBkCWtqO76/1ZywZSc/3cxdp+lZbxDi8lpdK1Qjfz9uxN8Jv6G38g19yFlRnnQWJLDXo2XgKt410Skwmb3yf4i1WV+KZV5pg0FbJdH1fAVuZxfRdfj+c8WjCk4LuoL9BS26/MbgoADZXda+5amPZF1iNjCPZTj/0M8Hq2n6Fb6fog4+ObKPMclwFZigwxdzF5UsjgqV5iUgWEiQKBCgsbAzzu4rB3Y6MRA5cjD3ebluZV4Y+LXaYcWA6GeVbDUyCVS2emedpqefAB2erfwaqqbP8OsO/UIpNaZE6RN3aeNyvNHUAkyDwIxGJlHiR+dQeYfNFc
*/