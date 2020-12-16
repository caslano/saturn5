/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
# define BOOST_FUSION_FOLD_IMPL_ENABLER(T) void
# else
# define BOOST_FUSION_FOLD_IMPL_ENABLER(T) typename T::type
# endif
namespace boost { namespace fusion
{
    namespace detail
    {
        template<int SeqSize, typename It, typename State, typename F, typename = void
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          
          , bool = SeqSize == 0
# endif
        >
        struct result_of_it_reverse_fold
        {};
        template<typename It, typename State, typename F>
        struct result_of_it_reverse_fold<0,It,State,F
          , typename boost::enable_if_has_type<BOOST_FUSION_FOLD_IMPL_ENABLER(State)>::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , true
# endif
          >
        {
            typedef typename State::type type;
        };
        template<int SeqSize, typename It, typename State, typename F>
        struct result_of_it_reverse_fold<SeqSize,It,State,F
          , typename boost::enable_if_has_type<
# if BOOST_WORKAROUND (BOOST_MSVC, >= 1500)
                
                
                
                typename boost::disable_if_c<SeqSize == 0, State>::type::type
# else
                BOOST_FUSION_FOLD_IMPL_ENABLER(State)
# endif
            >::type
# if BOOST_WORKAROUND (BOOST_MSVC, < 1500)
          , false
# endif
          >
          : result_of_it_reverse_fold<
                SeqSize-1
              , typename result_of::prior<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        typename fusion::result_of::deref<It const>::type
                    )
                >
              , F
            >
        {};
        template<typename It, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_it_reverse_fold<
            0
          , It
          , State
          , F
        >::type
        it_reverse_fold(mpl::int_<0>, It const&, typename State::type state, F&)
        {
            return state;
        }
        template<typename It, typename State, typename F, int SeqSize>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename lazy_enable_if_c<
            SeqSize != 0
          , result_of_it_reverse_fold<
                SeqSize
              , It
              , State
              , F
            >
        >::type
        it_reverse_fold(mpl::int_<SeqSize>, It const& it, typename State::type state, F& f)
        {
            return it_reverse_fold<
                typename result_of::prior<It>::type
              , boost::result_of<
                    F(
                        typename add_reference<typename State::type>::type,
                        typename fusion::result_of::deref<It const>::type
                    )
                >
              , F
            >(
                mpl::int_<SeqSize-1>()
              , fusion::prior(it)
              , f(state, fusion::deref(it))
              , f
            );
        }
        template<typename Seq, typename State, typename F
          , bool = traits::is_sequence<Seq>::value
          , bool = traits::is_segmented<Seq>::value>
        struct result_of_reverse_fold
        {};
        template<typename Seq, typename State, typename F>
        struct result_of_reverse_fold<Seq, State, F, true, false>
          : result_of_it_reverse_fold<
                result_of::size<Seq>::value
              , typename fusion::result_of::prior< typename result_of::end<Seq>::type >::type
              , add_reference<State>
              , F
            >
        {};
        template<typename Seq, typename State, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of_reverse_fold<Seq, State, F>::type
        reverse_fold(Seq& seq, State& state, F& f)
        {
            return it_reverse_fold<
                typename fusion::result_of::prior< typename result_of::end<Seq>::type >::type
              , add_reference<State>
              , F
            >(
                typename result_of::size<Seq>::type()
              , fusion::prior( fusion::end(seq) )
              , state
              , f
            );
        }
    }
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_fold
          : detail::result_of_reverse_fold<Seq, State, F>
        {};
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f)
    {
        return detail::reverse_fold<Seq, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f)
    {
        return detail::reverse_fold<Seq const, State const, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f)
    {
        return detail::reverse_fold<Seq, State, F>(seq, state, f);
    }
    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f)
    {
        return detail::reverse_fold<Seq const, State, F>(seq, state, f);
    }
}}

/* reverse_fold.hpp
VtFYG9OaQJ+Y9kk7rKGcMfHJySPHDlciWt7EcpIN5qNK8NPuf4py/I3qldmovJn/rLXOfFRtXMxHVeWnjW1NZhtmgzZZIluetyfZg7iWLf7rrx//rdjXcPHfY22sun48zDeG/Vgbw15fY9Xfj1L+Ht90R96gjz/5YHSnkX0OrQoa7XqselQj+QySz6aNjWWuyEb2OFJrbIehGIQReDoOwg44DDviaOyEhdgZl2JXfAS74ZPYHTdjT9yNvfFTDMcv8Uz8GSPluWH9sAv2x1AcgAPxLByLsZiOA/FcHIQlOBgvxXhcgkPwJhyKFZiI63EYPosjcBuOwh2YhLtxDH6NY/EPHIfKZ/d4x7jQO/a4S3AjoziTfMZAJxm/qHpeSCP7ehGyXk8365llvTA361U4bG+tTtwqxMMxMJvvs4yDMa+xzP29+j7vYjiWZw/4njvwT4+Pqe/nDvwbnjng7dgZy3MH6mfszI413o+faejnDRDPqvMzB/7t42nq+3kDe+f41T4wPoQyglJEWTnXF+/6p5eG+v2flzujXn7/39Kb7x3y+z9Wvk9lym+tNEqM8vvvTT6b1fPTW3LlZ2cXRSi50l7MCe+Q7683/7WtLdulLXPlN/AsSiyvrTBoi6Sgz1+YX+Rx3r6qLar7DPmqtiTI7/H2lCaUdpSBvDbuLU1blFZYusXMUZS2mNy0JVCdJ66qu1Lq7iB1n04ZRN1mF3XLH+pc9zCpO85PW/dg6i53VfeChZl5ubNyswsK61y/dd93SP2xlOMoZ1GGUn+Vtn5ySqV+y+H0uO74GPVces3s56OqL5L8tedAIq8N3mPcFssfcslYrVt7lPpHSf1VUv8Aqb+/1J/sqn5lilxbI+rehiHWPlAqln1vImNBhinng34b5I3Je9KL94Fz3XLvhfsC+nnelXuOTp639Z5YSoDBHOR7Gja3+li77+O7v3Ns3d852nMUtohW/j7QvCJg/qc7z5h69rim7au7fu36vk+GSb57YKbMlWLLb5Y87lY4CjvgaOyMSRiOY7AfjsU4HIejcDym4QT8HnMoFVLPXKnneEyTes6SfOOB2A4HSX2DsQfGYV8cgrE4FEdgAs7ARJyFw5D6WF++O2B7qa8J9pX6clivCebiSTgHm+NcqT/PYTtm2U4Hne1Mke2kynamynam4ek43WE75S62kyHbyZTtzJDtzJTtZNm2I5/NGKuzHdYtOQ47YDfsKP0XjGdhJ/t2+Fw17p9u0p7u0p5QaU+Y9E8P25xzFNnOAJ05586Q7UTIds6U7URiMPbB3tgP+yPF3l+y3XY67TtNtttKttsam2vy3OW+3B7P5gDk88blnH0H/D27P1YfOc0NdR/s/34PzNv7X57c9/L0npcn97t8c8T8e+eIOdr3s1zPD+Pdvaxt3LeqoQTlcS+LUkRZTamimObRd5QMSuk83/0t3+JbfItv8S2+xbf4Ft/iW3yLb/Et/46loeb/U7Lc62v+vzKH+f9CrM//obSQOcqbKnHGXbYxAFK7d/OxOT1nzVbfQalvGAZhPIZTX422PuaMcj8nn/X5sitPs8+XZn++LFqeCZmbJX9LxiIKf+O5qqrntWqehRkg8w05zwWV1Fg7/9hkAhBlu3XnXpOpx9zHB1XzXOmMTUiljgrdOkjMd/usfs34BE1e/nHNjZ/dbtYZKxChHLfd6rz88ZPik0aOHTauLmMFdrXUtilWNVbAFxv1xUaP/djo8Gjl7y2iH32g28Gw6s6dTvnmwxZDxrqPjco1mWu1NjZ6qsQsW2I7PA2DsBX2wDYYhW1xDLbDGdgeF2EQfo+HKXIt5hptqUfZzldST6hstyf2wl7YB3vjWRiOo/A=
*/