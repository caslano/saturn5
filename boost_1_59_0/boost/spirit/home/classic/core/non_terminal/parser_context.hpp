/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PARSER_CONTEXT_HPP)
#define BOOST_SPIRIT_PARSER_CONTEXT_HPP

///////////////////////////////////////////////////////////////////////////////
namespace boost
{
    namespace spirit
    {
    BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN


    ///////////////////////////////////////////////////////////////////////////
    //
    //  default_parser_context_base class { default context base }
    //
    ///////////////////////////////////////////////////////////////////////////
    struct default_parser_context_base
    {
        template <typename DerivedT>
        struct aux {};
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_context_base class { base class of all context classes }
    //
    ///////////////////////////////////////////////////////////////////////////
    struct parser_context_base {};

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_context class { default context }
    //
    ///////////////////////////////////////////////////////////////////////////
    struct nil_t;
    template<typename ContextT> struct parser_context_linker;

    template<typename AttrT = nil_t>
    struct parser_context : parser_context_base
    {
        typedef AttrT attr_t;
        typedef default_parser_context_base base_t;
        typedef parser_context_linker<parser_context<AttrT> > context_linker_t;

        template <typename ParserT>
        parser_context(ParserT const&) {}

        template <typename ParserT, typename ScannerT>
        void
        pre_parse(ParserT const&, ScannerT const&) {}

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT&
        post_parse(ResultT& hit, ParserT const&, ScannerT const&)
        { return hit; }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  context_aux class
    //
    //      context_aux<ContextT, DerivedT> is a class derived from the
    //      ContextT's nested base_t::base<DerivedT> template class. (see
    //      default_parser_context_base::aux for an example).
    //
    //      Basically, this class provides ContextT dependent optional
    //      functionality to the derived class DerivedT through the CRTP
    //      idiom (Curiously recurring template pattern).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ContextT, typename DerivedT>
    struct context_aux : public ContextT::base_t::template aux<DerivedT> {};

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_scanner_linker and parser_scanner_linker classes
    //  { helper templates for the rule extensibility }
    //
    //      This classes can be 'overloaded' (defined elsewhere), to plug
    //      in additional functionality into the non-terminal parsing process.
    //
    ///////////////////////////////////////////////////////////////////////////
    #if !defined(BOOST_SPIRIT_PARSER_SCANNER_LINKER_DEFINED)
    #define BOOST_SPIRIT_PARSER_SCANNER_LINKER_DEFINED

    template<typename ScannerT>
    struct parser_scanner_linker : public ScannerT
    {
        parser_scanner_linker(ScannerT const scan_) : ScannerT(scan_) {}
    };

    #endif // !defined(BOOST_SPIRIT_PARSER_SCANNER_LINKER_DEFINED)

    //////////////////////////////////
    #if !defined(BOOST_SPIRIT_PARSER_CONTEXT_LINKER_DEFINED)
    #define BOOST_SPIRIT_PARSER_CONTEXT_LINKER_DEFINED

    template<typename ContextT>
    struct parser_context_linker : public ContextT
    {
        template <typename ParserT>
        parser_context_linker(ParserT const& p)
        : ContextT(p) {}

        template <typename ParserT, typename ScannerT>
        void pre_parse(ParserT const& p, ScannerT const& scan)
        { ContextT::pre_parse(p, scan); }

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT&
        post_parse(ResultT& hit, ParserT const& p, ScannerT const& scan)
        { return ContextT::post_parse(hit, p, scan); }
    };

    #endif // !defined(BOOST_SPIRIT_PARSER_CONTEXT_LINKER_DEFINED)

    ///////////////////////////////////////////////////////////////////////////
    //
    //  BOOST_SPIRIT_CONTEXT_PARSE helper macro
    //
    //      The original implementation uses a template class. However, we
    //      need to lessen the template instantiation depth to help inferior
    //      compilers that sometimes choke on deep template instantiations.
    //      The objective is to avoid code redundancy. A macro, in this case
    //      is an obvious solution. Sigh!
    //
    //      WARNING: INTERNAL USE ONLY. NOT FOR PUBLIC CONSUMPTION.
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_CONTEXT_PARSE(scan, this_, scanner_t, context_t, result_t) \
            scanner_t scan_wrap(scan);                                              \
            context_t context_wrap(this_);                                          \
            context_wrap.pre_parse(this_, scan_wrap);                               \
            result_t hit = parse_main(scan);                                        \
            return context_wrap.post_parse(hit, this_, scan_wrap);

    BOOST_SPIRIT_CLASSIC_NAMESPACE_END

    } // namespace spirit
} // namespace boost

#endif

/* parser_context.hpp
TQS/xnQurj3ci/+9mF9j/K/rcA//ex3436Fx2iZ13xIwrKyjjrze+Ks0ji4lP7yHD2uO0Qd1UAN90Xfit+yz+OdtBO1QFrcVhUAT/PAnkqAd8M60C0e6mn406BwMN/PhXPWMUKgm/e16lJaXaJuptPYUEha9PmZrfKO3c28a0JuxvT5cjzp2NqLt6muhDmPO6XuueAKlPzrz1Pg+8maaa3FjR+t/0WIZ3dH6XS2WfpzYR4ul7TRRI0zkrO+jylJ3GlREH1WWfUjc05xozhpTJ388DarVru5BCh359Hcjplddiend2Mg/sRwbMTNEH+DnWP6Jadm4mNgCogusTBe86uotN3g+7oZ19ta+ijB9BGKDpgDvTbinRyDm5JTLOEXqwQzhlCGcIvVgXs1Gir6oRw/ml5zyDadIPRgXlzrBKRimf5djCrQdRA0nYaD+ooGcaWshUjBeP31fz2/11p7OrOaUBmtPtU8UQj6GCcg3hlBU2EfFplW88SHAJQ5gb8gGa8IwKG/hLsmGyyL35KL1aa6Q3b0HC6EUmzeqVbf23K52yt98A/vbuN9fyt98G/ts3O9q+ZvVbR6P+/2m/M2t/yDu9y9uNSw+JKK+JDGGqK/9s7y0JZS/mQ4KeWu7PHSReWs7StbCv/NuhTIVpmVRVuXCbJbo8WGzfhAdNsyeDfnd96hx7CDcJWYPJoxQMTFheFwIl9ee55D16sraBGyiZvpoQFNTMz5xPjbL1pL1tWyizx4J/eLehWdoE6NYeMPEYZY+dtky3F6vApVU4H/6/nfj+0a8cnCLSVStNiRcafPrz4HjgtdkQhZHFja9eQH0f0C7rJk3xNCugE6/GcPpDE3YEsRgS7+FJ28VYsKlyN/d+G2XvxuRp3tyzwS3yN9pdvrdOLnHXTTm6sRzp2L77vMt/8u+u/c2AO27dwOwUZu/qJBTfs8p6I+/aDSnvMIp3ZxyIac8xSnov3/XBbfxngpxErrrLxrFmX7IKRi9v2gkp/g5ZewwucsSeU+NG9bTUMvd2FPjh2FPyYa+uPs7e2r2kVY9PBlLANom5Y+92Iz79VYTaotxtM5XV2KNiD75JOiUSyFOvEhgI5cuQS4KL6hWbI9maNXleuh3iEXzEi/brUHdj+WVRfXnirDIulInS8ybpE0eQ+2WnwjdGCPFBk1ipjeX6hefVsOHir7zjmEgEPzi6d18eQcrK3Vldz+z5XkTzRp4WQ95uIZs1PCiUcM0o4bc+BoecCIEN/yW7+miytQ9RYCccsK+CIbEe+8fOJwuHRA78HdbcSWJzr33goxfDwUG1S1Kd+OwRpvgNSnhwd1QFsJiQIb+9umT9DbOePstv4013n5Jb3KC+GiZu5bWlQGXj5+R+1HxEvlqE6MO4BXAxGeZg19XyddE8e37eMUs8Jn4VdepeArieJeMYEoUROGVhC8wrh7oH6z3nDr1m3ug3xSYje4PgRkh211LEJX6p+LW3xiis99NJ/5sO1LzcUt/4RtEg1ebojNfDhHfwH2//T2LzrSc9vLK0jHlevENnq5l1zrftpVC9ykxAUTbFqrDEJXltE/3dC2tg5DsifaTulD6Q+OL9bTvajupHza7VW43u2Wxs/7AljeMbg3jbiGVu7VyM3frDtmtnV50K3RLrEc3UY+uoB5d2rtHo119exQdJHtxrPUkxoMOfnaKOnjMDoGLpeKyH8GYoR9ABkjQwKp8D2FH3Lg8GJksBVplBwp32sTvPOBv7eD1nkFNT9sNegBIMtnAfOWVj8NNwBBtOELZMMGPSIvKBG0NcPSKKoCTWDQVNzcyAdAmZsUlABjFZEqI3iqTItNT/EbBKzxmvsh0u98oPCQu0eE3Kui+ucU4F7RVwAL6NpwO2hD9ORh2yS9qBadx0aBF3Hyq1ahHXAk/hju5NOMQfSfnTJBTIq8ZC5hWTEIhxn8G9jCmoXiERC4xpCKnIpqYpdN0ZEZ4X4n828Db8ihm8k/uezb9LCDw/21bqx7N1Hciq3ZUpJ4+Z6LSyJ12cQGNMLJyvHx1iIH0Cq3UpvvP6LoJdoOTE4yDTXtoTOZDGTnuh1zKZJG5yQC+l6ZJ0Wo+lD1ehoxA7PsIugktxE9BRpsv3ihsYxnwLwmQsiqjSULLP6OLSLIk62kGWiErpna/+MlptPuHX1C7LyXFE8rphOXFwqt6E8rAUWJD+6l4TPAsv8bwxMl/ExndfRHEbkiLQyif/BvUbjcnxpBOJSfiNQ4x/f7fkMXhFfR4fhwGW9bJgZT7iQtfZ1EaL0j5VBbD2YVdJvLSLJGJ/cWpX3MiL9ICSgy/AYxteQdIVmW0Gn4Dp4BFlcjXkMmhZpbJdXpZJseVRuVvrutLL+pi8iX8BuAN9PbVSVI0ygvptWFCDei8iIU2vE0JlgZgp0LNM5pNS9pr39K29Yu2m6QGkSGn+fjkSQSRQXnKids6aYvIWi47bbyni/xEwlV8gZWcQCl8fgUTsk4EqAu547Ts8fl5gYA/mBCJbAFF9/ZSKKriJ5SJ/OVgzxKU2yLlmxBw1cikrgTSZ7KA13oBuhVBDuoVRMM3U8cg3Nh+shW4/9VuwzZGFn/5yTZdZNpAOhYlEelYMS7ZJCB7lO7h4dJf1JkN8dDBAAiPMQlIOcspb3MKFGf87/0cfERAbAqAFnElSvX5/DnxdEjWCYJu94WhqQiPJ54lvOxeD9AtGWAqNEcfMu7HY9eeoJlZfiavOeWrdkTrEhc6+IpzJK44U3DFiUbzCsyrzehAmSKm3ULTMgiNFkhPnuKWb87zvPzyP62GrnuMGI6swfjE3qw2vkFew0pBO+iNZUJX0QbWDVk894QPCKOd+sktOkctmkbV9rrvhXfdnw0khqXDcyA0yr0kPTSc+vsM9xet9vSY08RzVBNCr5z7plXPzzfV8tCgqnTLO03Wzxsbr+zO/TketLi99tBoVnc3yhjK7kZcAxsXkdqvZhGkSO1XmQKz1o9on0x8mcD1woQYETSHAETjwUq1cCsm85NmUDE8T0N2ASAxgYxsjvArIIjBs7ESr1vlq0V4esQaNRcROEYSTPwnFwvUG6/W2uh5Oa9zaZP2iBSmA0lyjvKOx2MARN+N0vmigAoaVH5WJSAvyYC8EYSJ6NwlDqpdm+tQE8OPj7Y7yw9aelT6/f5dNhdfrrHXWq+dXfKv2UQvwQG0ZEUIfy4/6p9uSVRG6F67cQEn02gVln4SfYxhiB0a31xFDB6zELKDfvFG03ld68o6oR3xnFMuCxSdoQ0k9GvhzKuoi37TiFuvlRfqCxBS4WpK5zwnkGpmOcIF6MdNlAdH3FP076IF7N49uLTip1jCfTqYONw0oGWt1bxrcBLyFTfvbUXkzUgxQi6de6PD2CuRciSwLuMFWIAEXSmL7MHq0c8JDfCmc1SfUD8c3k8OsgMyHmeBeH7+KemDVk6ddLFTyP7Ppe8Or8j0NgT1XH+AlfcCxgSF9xHdXL4UIkleArVwHWS3DyfIS8EX8IKY6HwxiAs/1feCyJ1i3vltkt0O+17WJTYsF+eNofjFXfRb9W4lbDFR/CJIaO+5IF9wb4274Jbf0/wSRMUXGdAh2ap6X9ZTX/iUEZItbs17vVJRtXALQKR0fkBXtrAzUTmqAzVAJJsivg28JQRoKN8G42awvHLZReLFppO67t3Sp363d8vSHdGBmhfR/8RDlCcA/5JcKRxTAAUs+tNsor4FreL1vVy9HKd47uvzuj9A/wXhDGur0YW/yjyBooK4+j3edaVW+C71bTIOi0HUhrvwBWf5Wmyslbjpifi25QX84t6f4BqpWLOLM85WdrwaFxePnb1ovnWRaQkDnG9X0qJeFNdMHItpb42xmKkb5Y1w7M7kYbBeLok68mJamdag1QSOX7/Lt6DD4qqWJxlD7SObO/j6Y+G3pn83UFGecz18je2VOMtBi304C3UbsTdu6bbE0VX9IIBMTjfpKkCCRHvizapeyOyNv4MIwuvoy1KMnvMKR/gDXqVi7Dr5wSpC/AGvEEEyedXxChM/jPMX3hxTfMU7U1oX0DkQZuKO9V+ppzGx0FPnLJYidqB39hffVTy9GLMyycjPNq0F54xhVieX0fC1WRlsdX6QMlv/Toi4dLwl1F9/dIz4HNUZeFl/i/DD6XOY1Cljtbxxnr0PW7Mq92V79qpTxo6q7KzbF/7BWDMwBviYGvHLhrY+ThZqRFt8WpyThRox7u9tPU4WsGa+OF7U/4s+khgcDbPGemaNexg3cBdrOelarfPND635Y/yz/bCBuqvxpB7e79Jzxpoiq6Crot8rNHztrEWaQzfixu6L+2BYkCIDl4as4XSLVujQSgjl2Ku9LtMMmoO4XqHl1BREZsFlEWVNs5YK3WePNsKi+OAvW/WKD8a6XPuiI6g2+pyUWWhX07IqYSH2Ii2GEWShUWwuRIPE/1M34A3AVXE1enX6THyvcrlX7A3AsLjnHqRTD7gDc6BcgtYFWp+J1nOvoda5PaqAmuR1axE3orkDwoPWTHO2vHyzpS7xxb303ah1HhKSCuHhh32OUN986Nv8WN/CB2rQvd+iUKEjfBnTwaBw40zGdf/dCBuSgUlQp2dErepjGdr0DJbwpfo/HuYKV09kA3mPOSXPwWTFaxcvnZGdpCEVv0pD6sCQYvAwdzuL2yXQVudMFPRP+L4MS/i+sRaV1t+LINocZnsMzNFzxjO8uGJGcPd0AeyDk8SxF/ruEqcfEbIfHQPXKatxrswaq+aOFcnUn30Vq99Pw8SqU4qrV5RZpItJdcVy/ruK/+IC3IB8r13Lm2OtVacs0RLUvLt1/zgGvdEVx4upC3/r5C4MgNb10rvbDb2bOjjxELf/rZ2VjeCnJtsuOfzZKXKK6sSjlFs82hWP0357WTvmI/wG/GVbVPb5WJ2c0T8m3IW0D9ukmEOmK+756aElYsGVponLYi3nnsycedqgdSNGujJzijJl7GXTo52WM6cgmJKnzbo7sybclEw/5lk/oL/F4UqrPyC6x7QhVqxBoRMl/CegJrinI9z8tvmbJWjG4Bs6aPBntDuLCdMkhx9Pl0HNn1hBgG2zWJRTkUVLA8Ldr02X83P3grj5eSxdXF2P+SnN0pT66NUcnXa6vsSu3ViE9RFHXpWKxyGnpzo0UHMFcHLAbXd5h/KROYnXU5W0Q57C2jlfqBRX0HLQPIlhhHuN6KAA8wkTQdFw6M9x+oTxsZexG1+g333C8hSXmzGdk8Shl1nXNC76kZ0y8Ks891z/Zvd25a+CSAIZZZduWeRyzcDMjMDMhIaI7Zeb62TG8OoJypLWJ+qoEcVX9Qo6odN+eVbXZtozB2qnOCxnuHLA5syazeEz9hJr0D4fgVSqgudVbzMcpMXiUEzA0DSO1kTQaIQQ2JhOiX4ZtvyIWIwIHFPtmq870yqDiXX9xWJGkeAddr4d4F1UiVP6Z8+am8w4XAbks72cFNIQcGBRZGBgRLIPicv+xLZ+Q8r1UH+tH5GxR3U/ACRRqxYlp3uwlwRpqnAcz9TVMr520CbqaMaMVYv2C1pEzeXMt0n+G3RCz+khI4WoORly/aawIYgnPBlx2CyhoVqy7r+H0ocaKcrgzpwMuJmNrQU21UfEBbywd7b4NbXT+2Dy2d3stTc0h+onLgKLr0rfv/DKS/SPYMXC8QZ0UErH16zJPWuOEcQLTtgeLeY95Bef0UdOlgGNua0p6PgF3PEUbZAYDhFCXnBcTM0whickShBT09tjp2ni2r73GsTjr3jSBtQGVt9Zzt4yp9rDXf0JILtGKTPF2W7u8m0ECCfpZ/Rq2MzwyNDDm77mrxlGh8dgNJZ8AvV3/swQ77ic3cY1/RxzYMTfs1ImzwElGByip66jgb1joX15X3lVaB5aFteGvGGRGpoQFsNCo3NzQ4Nyc5Vb/P6iaqoimsKWBBZiOqP9+WeiVWIcGYXtBU5LwOd/808rfn4J9un1tPZeRj2S1Re/gFiEnZ8FE0TWed1cUSDaHV/FvlnECHwzC4ebXfkcPltGMBNNVHmslm8QLJUjo1iUsUSgAOA5+EuLv5oDAeEgqfa2uPif9kTsmif+ck6fv9AIxKO1GrjdnLEPv8KMhQbFOvM0h5RdGBe9q1XjcwBx3SpwLIUuJViPw0BrMJY6sR5UQbbDU60Mpjn5uLFVzgk1y1U732b1XrBDjXBMVx36rIB+456Gfv9VG9Q+bqTLczQ0TBtSEEwoCEjPXH59tiP6tufLWEzwgrwC+SWIo/9lWuPoy3JKB750Vq9OHj+QAPPbNSB8Zy0VRdcRP3SkOidEYOCvzlnyEiakDGpQB4hzB7wrCfu07PR9ElGm8vZ3iqfTTUQJepSADHTukyBbfgabb0nnoiXas4byFpUephGdco9EJP0Qpp2QjTZrKa5iXPUnTWHE7148qwtLq3nq9goERZSGcbzKYDwcy9FOONi90K9cQQfuQBy4yQGRfQnwUsDEQkRJ9FMX2ZogYgCdshI0BRjap/DvodCFKJbmXpitDCOkZuXC7CWFS7sXpoVytJyx7nntiP27BCaXQzhaq8B1FuvfFQ1h1R+iwcZGCpsD+pJ2WpkiQvyaryvT25zpa1FnFUUJlakLizSfUHMWo6JHi6wP2ahrj9mi11M3hqMbQwLi5+m9eg/T0axKuOw5UkAFqQZxx6tnEVcI12U4FP65A4eCy9wg4+JnzCXjy32mzSxG4Et4aS2BOzPo8SKqMJbUWXYB5EfbLzKW1Vk2IAHBWtxKmrPsFUwae9y6B5pOUP3P0jUrAmZqh3qFZFqLqEPuCVveZ52A7YyOrVkdOeLF1aeIvwzkF3AA8YjCkas1pQ4qVLNDtG+epHb+jMIlKc4ydEGbOtZd3O4s+xUnpoXGxnoQutpdMjo0VvzxRDthxM6pfEg4y35CJGSWPr3pR/SvkRg6vtFCODqatBFxxwzqjqhVYpfrtBbaiplTi7QFY62EH0rqN29+ZXPm3uCQD7sic+s3z1a9Dfoj7VpCgHjm6ChdyUAQlXRdGa0raewW71hBvrhkHa+CXINF27EG6TEklVWZX+Cekha6w80UbGialjfWfVt7aJL2+BztocUBbf7dWnXmAes+6R7U2xKx3cQvWl6RNe8eJHVpU+YRXettV+fSpLUsiFojD80BuQu/oZulj0JTnN7RzJTeYyA8T4XmMl424iDmikGacTtSnEn7vR8L1Y9CnXMtC8R8rkAAnIOutESTaH/o4/LFvm87TYPVR+pwT8JnsPjxN8xBVbw8QPLwTIM8QW0XrQXq+GbVd5nhUqjCXvdNPBl9JE400LSqL5uJPY0b8+kA8ukhNSekTV+i5iyJTF/KSOvUxTSIp4AsF6kr8Y9kNUdXLBpNncnHRChEa3xGoC7OrqE6phZn4c7xB+7i9NDdcYj59Jet0BythhTkKNGSywgtejpDKYSiY6Edc9KdZf/GJM0sjkxd6hcOOojpt0RlM4sJIZuoTH2y2NMp45WxOygIJyKPzGHfgEF9c/BbSOVMZ6/MAFgJkVhVXzOcIetKHYzda6iQOhV0RrGE+HGS0OAxTC+IpzbETaphJ/nrq1rQJ0m51/tF0TlwbfVsuH+B/shS+qbuWo71KRzVpodfx09L1MHR4WcuFa9fBKEY
*/