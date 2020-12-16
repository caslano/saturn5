/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1, typename Context>
        struct result<This(A0 , A1, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1, typename Context>
        typename result<new_eval(A0 const& , A1 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2, typename Context>
        struct result<This(A0 , A1 , A2, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        struct result<This(A0 , A1 , A2 , A3, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx)
                );
        }

/* new_eval_10.hpp
hADmws/TWLgtXn2iVjLHs3QQ2EgjeEb+Tpxejgnm72rM2GMJR7qq1huBJnB/Aud51vhajShB+6p9lP42P+9pnyc18eLijif1eVIs+d+LoX9EAwYM1jiO9YEKabXo8HSXKXlIPghq3yp62+a6EhYvZGkjeGdtQAemakVWtn4cMGlxsTyhOVseGUI2aSANaINb5T+LUusOoE4lO2m4cPDRe1UNYj04U8xZ8MnXBVCUIVl+fOOYB5MXjKRKayjhyBmLb1gTHAGT+USBdF+Og39AIAlEu07w0IWJswqPzaAqfKN8iP2RSu9/f0rr6U7lvRpxGoEAmnHgfoq4g8cTkSVymPU7EcVZCo+jc60UEigcQqyXTLH9qFXQn2NN/aCVNUu65VyoAv4lZaE/hLGc7sneBRhWrT0cpgXSpD2E4vxLfGVZDQtAHOmaPvCvZ44RVkgmw79W6zOG1iCYak4P2KdClcxCdY8TudZj9QvcRCBYKpDL+UAd8cD8ZykbNYAMguA+j9fJ69S3PmsgQXqGvY/jaAXWj3oTavHOT8hzN0jIWR7o52zrhAsPtuYytmsohZ92oFPOUQcOdXxUUwc6uCCaKBKknwulHiQDK1Xpz1WhTWw5vfPClPqujl6B0cJZbXnmiTgYFfgPT9MUhRE3sUE/7LVTuy4v/W3/qfVta1IDnDXRgXn78ttG+BTzoWgxpGmPYm31k+pfUtN5wdKsU/f/8QwUWx8oimHQyjnh2dN9GVvn4+kAHT2BrBque8u9S857qXP9ozkwCNCzUJ2Xlnd60QCDWVvgn5X4FHnHU7pAsd+D8GOBM9vDx688H+38fiFAMD6GiR4vis7X+jTVeEDtDCcCfmSyO7ANp59J1pJvYcq8aQ0z2XNu1qxojezmcgq9nWCu1ImulkSncyKclc1KjDGsRynIX38VsvZSGIxtvVozIEg/e4DF0UxasvloGejjzaY2jPWT6fzUI5lO9Fk/B/PgqYCTOLph4Q2kl0at+PjwtGHh9SkcSFl4eTTnlFumUUqRA8q36GFRE+o9q6Pr/DpSNuijlaEFgXC9kFByF8CqIQ6GNdiBsW4vLJ+WU7xpNvz7JTTsM9JGZjn4pJmGPMJcP9j8tY5f4LbjPRwP6FF4wFwN8bQ0zTHXghcF281SbN146wyCTAkH61ExHRu54gGLN+jw1Jo/qVTd1UYk3A08LEhf+281TNjvv86FUo9LbY0PIKG8y/LvfM7Pmh15r5HRayiAJJSswFV5fpPfk4RJoI8LjqFWha7GDfGgXxANtic82wyNBN16bUbBCE4B9DGRtFYFq2FvvZoFSY/V2CaTjq1Jr8HMsIMjw88UjOTorGaS9XiKw+unQo8UHE9RD2Kxsq0VHLMjDj+JF+OGou8wT2vab7+RpP/lJ8jve7X9glMfV5sZMHm7h+WE0x4XgX2Sz1/2hVz0TAX+xlXOBCbMMiTRMibMgtVMuMkwThDnz5eYbI5B7Eybhm6HNGBwsn11LGeB8vCTKTmcIcNAfv3DBPcwNgoebFGf6u5mfZ+8OcuI4+5GS+aXZ0F398I0yj4X1SL8uVoB1AG78iUP5DDuMVXVWpLn+eXnUtULSubVuooGFORwbeZJbRY9LPWcyjFFEmNyDMjIwSFYtjm3L5a5DvudBzyvVcUQ9aMwwTRFOHU0g73BLYJ7NgPHKFpGdwc4KlbC57p5zlW02LL1PQ+8Un1IibE1kxhbM+ysMeEenufpLNAHo7q0VyO1F0p/Z8AJR8nPXSwMRpvaVz9T7bNPiLmxwvsabGwLjgXRLaxGa1JpAOdmn3qOgdvSBhbhBuQEA6NvwWVQQiWi3fqwKt7+kLugQJV8HzaPVaejqOQ=
*/