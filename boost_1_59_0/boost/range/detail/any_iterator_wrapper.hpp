// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_ANY_ITERATOR_WRAPPER_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_ANY_ITERATOR_WRAPPER_HPP_INCLUDED

#include <boost/polymorphic_cast.hpp>
#include <boost/range/config.hpp>
#include <boost/range/detail/any_iterator_interface.hpp>
#include <boost/range/concepts.hpp>

namespace boost
{
    namespace range_detail
    {
        template<typename TargetT, typename SourceT>
        TargetT& polymorphic_ref_downcast(SourceT& source)
        {
#ifdef BOOST_NO_RTTI
            return static_cast<TargetT&>(source);
#else
            return *boost::polymorphic_downcast<TargetT*>(&source);
#endif
        }

        template<class Reference, class T>
        Reference dereference_cast(T& x)
        {
            return static_cast<Reference>(x);
        }
        template<class Reference, class T>
        Reference dereference_cast(const T& x)
        {
            return static_cast<Reference>(const_cast<T&>(x));
        }

        template<
            class WrappedIterator
          , class Reference
          , class Buffer
        >
        class any_incrementable_iterator_wrapper
            : public any_incrementable_iterator_interface<
                        Reference
                      , Buffer
                    >
        {
            BOOST_RANGE_CONCEPT_ASSERT(( IncrementableIteratorConcept<WrappedIterator> ));
        public:
            typedef WrappedIterator wrapped_type;

            BOOST_STATIC_ASSERT(( is_convertible<
                                    typename iterator_reference<WrappedIterator>::type
                                  , Reference
                                  >::value ));

            any_incrementable_iterator_wrapper()
                : m_it()
            {}

            explicit any_incrementable_iterator_wrapper(wrapped_type it)
                : m_it(it)
            {}

        // any_incrementable_iterator implementation
            virtual any_incrementable_iterator_wrapper* clone(
                typename any_incrementable_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                                any_incrementable_iterator_wrapper(m_it);
            }

            virtual any_incrementable_iterator_wrapper<
                        WrappedIterator
                      , typename any_incrementable_iterator_wrapper::const_reference
                      , Buffer
                    >* clone_const_ref(
                        typename any_incrementable_iterator_wrapper::buffer_type& buffer
                ) const
            {
                typedef any_incrementable_iterator_wrapper<
                            WrappedIterator
                          , typename any_incrementable_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual any_incrementable_iterator_wrapper<
                        WrappedIterator
                      , typename any_incrementable_iterator_wrapper::reference_as_value_type
                      , Buffer
                    >* clone_reference_as_value(
                        typename any_incrementable_iterator_wrapper::buffer_type& buffer
                ) const
            {
                typedef any_incrementable_iterator_wrapper<
                            WrappedIterator
                          , typename any_incrementable_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual void increment()
            {
                ++m_it;
            }

         private:
            wrapped_type m_it;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Buffer
        >
        class any_single_pass_iterator_wrapper
            : public any_single_pass_iterator_interface<
                        Reference
                      , Buffer
                    >
        {
            struct disabler {};
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassIteratorConcept<WrappedIterator> ));
            typedef any_single_pass_iterator_interface<
                Reference,
                Buffer
            > base_type;

        public:
            typedef typename base_type::reference reference;

            any_single_pass_iterator_wrapper()
                : m_it()
            {}

            explicit any_single_pass_iterator_wrapper(const WrappedIterator& it)
                : m_it(it)
            {}
        // any_single_pass_iterator_interface<Reference> implementation
            virtual any_single_pass_iterator_wrapper* clone(
                typename any_single_pass_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                            any_single_pass_iterator_wrapper(m_it);
            }

            virtual any_single_pass_iterator_wrapper<
                WrappedIterator
              , typename any_single_pass_iterator_wrapper::const_reference
              , Buffer
            >* clone_const_ref(
                   typename any_single_pass_iterator_wrapper::buffer_type& buffer
                   ) const
            {
                typedef any_single_pass_iterator_wrapper<
                            WrappedIterator
                          , typename any_single_pass_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual any_single_pass_iterator_wrapper<
                WrappedIterator
              , typename any_single_pass_iterator_wrapper::reference_as_value_type
              , Buffer
            >* clone_reference_as_value(
                typename any_single_pass_iterator_wrapper::buffer_type& buffer
                ) const
            {
                typedef any_single_pass_iterator_wrapper<
                            WrappedIterator
                          , typename any_single_pass_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual void increment()
            {
                ++m_it;
            }

            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == range_detail::polymorphic_ref_downcast<const any_single_pass_iterator_wrapper>(other).m_it;
            }

            virtual reference dereference() const
            {
                return dereference_cast<reference>(*m_it);
            }

        private:
            WrappedIterator m_it;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Buffer
        >
        class any_forward_iterator_wrapper
            : public any_forward_iterator_interface<
                        Reference
                      , Buffer
                    >
        {
            BOOST_RANGE_CONCEPT_ASSERT(( ForwardIteratorConcept<WrappedIterator> ));
            typedef any_forward_iterator_interface<
                Reference,
                Buffer
            > base_type;

        public:
            typedef typename base_type::reference reference;

            any_forward_iterator_wrapper()
                : m_it()
            {}

            explicit any_forward_iterator_wrapper(const WrappedIterator& it)
                : m_it(it)
            {}

            // any_forward_iterator_interface<Reference> implementation
            virtual any_forward_iterator_wrapper* clone(
                typename any_forward_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                                any_forward_iterator_wrapper(m_it);
            }

            virtual any_forward_iterator_wrapper<
                        WrappedIterator
                      , typename any_forward_iterator_wrapper::const_reference
                      , Buffer
                    >* clone_const_ref(
                            typename any_forward_iterator_wrapper::buffer_type& buffer
                        ) const
            {
                typedef any_forward_iterator_wrapper<
                            WrappedIterator
                          , typename any_forward_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual any_forward_iterator_wrapper<
                        WrappedIterator
                      , typename any_forward_iterator_wrapper::reference_as_value_type
                      , Buffer
                    >* clone_reference_as_value(
                            typename any_forward_iterator_wrapper::buffer_type& buffer
                    ) const
            {
                typedef any_forward_iterator_wrapper<
                            WrappedIterator
                          , typename any_forward_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual void increment()
            {
                ++m_it;
            }

            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == range_detail::polymorphic_ref_downcast<const any_forward_iterator_wrapper>(other).m_it;
            }

            virtual reference dereference() const
            {
                return dereference_cast<reference>(*m_it);
            }
        private:
            WrappedIterator m_it;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Buffer
        >
        class any_bidirectional_iterator_wrapper
            : public any_bidirectional_iterator_interface<
                        Reference
                      , Buffer
                    >
        {
            BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalIteratorConcept<WrappedIterator> ));
            typedef any_bidirectional_iterator_interface<
                Reference,
                Buffer
            > base_type;

        public:
            typedef typename base_type::reference reference;

            any_bidirectional_iterator_wrapper()
                : m_it()
            {
            }

            explicit any_bidirectional_iterator_wrapper(const WrappedIterator& it)
                : m_it(it)
            {
            }

            virtual any_bidirectional_iterator_wrapper* clone(
                typename any_bidirectional_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                            any_bidirectional_iterator_wrapper(*this);
            }

            virtual any_bidirectional_iterator_wrapper<
                        WrappedIterator
                      , typename any_bidirectional_iterator_wrapper::const_reference
                      , Buffer
                    >* clone_const_ref(
                           typename any_bidirectional_iterator_wrapper::buffer_type& buffer
                       ) const
            {
                typedef any_bidirectional_iterator_wrapper<
                            WrappedIterator
                          , typename any_bidirectional_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual any_bidirectional_iterator_wrapper<
                        WrappedIterator
                      , typename any_bidirectional_iterator_wrapper::reference_as_value_type
                      , Buffer
                    >* clone_reference_as_value(
                           typename any_bidirectional_iterator_wrapper::buffer_type& buffer
                       ) const
            {
                typedef any_bidirectional_iterator_wrapper<
                            WrappedIterator
                          , typename any_bidirectional_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual void increment()
            {
                ++m_it;
            }

            virtual void decrement()
            {
                --m_it;
            }

            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == range_detail::polymorphic_ref_downcast<const any_bidirectional_iterator_wrapper>(other).m_it;
            }

            virtual reference dereference() const
            {
                return dereference_cast<reference>(*m_it);
            }

        private:
            WrappedIterator m_it;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Difference
          , class Buffer
        >
        class any_random_access_iterator_wrapper
            : public any_random_access_iterator_interface<
                            Reference
                          , Difference
                          , Buffer
                        >
        {
            BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessIteratorConcept<WrappedIterator> ));
            typedef any_random_access_iterator_interface<
                Reference,
                Difference,
                Buffer
            > base_type;

        public:
            typedef typename base_type::reference reference;
            typedef Difference difference_type;

            any_random_access_iterator_wrapper()
                : m_it()
            {
            }

            explicit any_random_access_iterator_wrapper(const WrappedIterator& other)
                : m_it(other)
            {
            }

            virtual any_random_access_iterator_wrapper* clone(
                    typename any_random_access_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                                any_random_access_iterator_wrapper(*this);
            }

            virtual any_random_access_iterator_wrapper<
                        WrappedIterator
                      , typename any_random_access_iterator_wrapper::const_reference
                      , Difference
                      , Buffer
                    >* clone_const_ref(
                           typename any_random_access_iterator_wrapper::buffer_type& buffer
                           ) const
            {
                typedef any_random_access_iterator_wrapper<
                            WrappedIterator
                          , typename any_random_access_iterator_wrapper::const_reference
                          , Difference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual any_random_access_iterator_wrapper<
                        WrappedIterator
                      , typename any_random_access_iterator_wrapper::reference_as_value_type
                      , Difference
                      , Buffer
                    >* clone_reference_as_value(
                           typename any_random_access_iterator_wrapper::buffer_type& buffer
                           ) const
            {
                typedef any_random_access_iterator_wrapper<
                            WrappedIterator
                          , typename any_random_access_iterator_wrapper::reference_as_value_type
                          , Difference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }

            virtual void increment()
            {
                ++m_it;
            }

            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == range_detail::polymorphic_ref_downcast<const any_random_access_iterator_wrapper>(other).m_it;
            }

            virtual void decrement()
            {
                --m_it;
            }

            virtual void advance(Difference offset)
            {
                m_it += offset;
            }

            virtual reference dereference() const
            {
                return dereference_cast<reference>(*m_it);
            }

            virtual Difference distance_to(const any_random_access_iterator_interface<Reference, Difference, Buffer>& other) const
            {
                return range_detail::polymorphic_ref_downcast<const any_random_access_iterator_wrapper>(other).m_it - m_it;
            }

        private:
            WrappedIterator m_it;
        };

        template<
            class WrappedIterator
          , class Traversal
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_wrapper_type_generator;

        template<
            class WrappedIterator
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_wrapper_type_generator<
            WrappedIterator
          , incrementable_traversal_tag
          , Reference
          , Difference
          , Buffer
        >
        {
            typedef any_incrementable_iterator_wrapper<
                        WrappedIterator
                      , Reference
                      , Buffer
                    > type;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_wrapper_type_generator<
            WrappedIterator
          , single_pass_traversal_tag
          , Reference
          , Difference
          , Buffer
        >
        {
            typedef any_single_pass_iterator_wrapper<
                        WrappedIterator
                      , Reference
                      , Buffer
                > type;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_wrapper_type_generator<
            WrappedIterator
          , forward_traversal_tag
          , Reference
          , Difference
          , Buffer
        >
        {
            typedef any_forward_iterator_wrapper<
                WrappedIterator
              , Reference
              , Buffer
            > type;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_wrapper_type_generator<
            WrappedIterator
          , bidirectional_traversal_tag
          , Reference
          , Difference
          , Buffer
        >
        {
            typedef any_bidirectional_iterator_wrapper<
                WrappedIterator
              , Reference
              , Buffer
            > type;
        };

        template<
            class WrappedIterator
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_wrapper_type_generator<
            WrappedIterator
          , random_access_traversal_tag
          , Reference
          , Difference
          , Buffer
        >
        {
            typedef any_random_access_iterator_wrapper<
                WrappedIterator
              , Reference
              , Difference
              , Buffer
            > type;
        };

    } // namespace range_detail
} // namespace boost

#endif // include guard

/* any_iterator_wrapper.hpp
pcAw45WA18v5wz57t9vJw/7fnLeHh/0LkYdeE+nAHLx0ae59QmNgqz+mnk6u6txOqkt4qDwVXhzvifcWC1PeK9UDU34CJQFIKd3QrGAFHX14rKRELX2+tnTKCgb8+MGFxXkTeCrTI9jIiQ3suuz8FX2KE8XWKtA91R1NA6Uxgx1LFlfTfkh7bSisyLbr4VgWIYT0M1jNzFLyR+9mtYLSB0l0xsM1eSLwLcO+fA/KtMKMzXpW4ZB8loHACc4SNQQU8Ogwn/u9xGvzEeFQhp89cMFsdGbNIEzSPfp80jwwsA6eBgeyOKd7vf6bDP1R4rUmsV8/uBDOQqDuenzbjASa6AffOICTPXPAC1cXBbxTbmt+d50XWNDvw/kbg7aEMAB2szZnToKg2XhvLLqE3ZmMBMj9I4WrjBCwj76A0lzk3oANr6Dgn1juuWnwoyFs8n9bQJLtDVpAhFnZLklZ2KYB3FlgG+lzAQ3IdWFAI3na2PebM69tM6si12wcjS2/bI3wHn2a2u5QVNdVue6VXplrvi6OlPdjl0+f6m4xBwDRYIKRCPDR0eZ9rWd3kEyLeR1A06lnPc/AQJ98jcFvywJoq+dDzAJoW+RDMHhpo4BF4YtMnc91VEq4fLsd3vVGEF6sVxDQYHJ1Af4AjwQxGQiq+n19QR1CzgK7AT32xgF2AcYdV81KtbQO/50FJiMFCSy1C98K18FwWX3oiSscwI364QkMcSWQ/awB11uilqfsHsyrEWU+ZAIBpIuBphN75UHy2TIXzVH+7LCKiUp86WMaTAC+YVXCPQfdrdUPqQFlWoYGANxQK0PVJ1jfax5xyTIf/cHjN7VaKQtCr7si+MFIXVm7ufUBxA+IaCPy/u8fba9PI0UtqQVQAMK+I8RN5taO/5YEfquHrT+Ii4t/B0ffVltrx8Um5w0ro4XxFCasU/vL9bl5RfX1A/DrAdqfH6MA8Ky3lLAU/7jvhr6X8c/Bl/JNhF1jxTeopClI1TG6M0Omd0d8EdfkasXKiAfbikm2h7IFwkqtPfq65giehLIFfVsi1MQ+zTgfgRWWiAzVz3KL84kN/Ve+Wu2FAM+8M5AHUbEm1KQm6cVZ3VT61723qY2pto6AlqVZ3g99q8cv4Xe9qGu/uNQOljunHRV3e03nQ8cRsj4XXrvTtE9mwt/i5w0MfpFBQ1PkN1ghYDysho+mK2RXMiBJd/280mFlPK22+dKb+HUB4W+xx350gQMDCIizKaGOl2Pc8HeWY/oy3hmnFjReZv2pFTfWMuB+hSnm6wYfUGv/XccsNPTUAHeJtt/hUj67l1dOvDX6I52pd6qA6KByERggXB7MyYGj2zh5oKYgwc7X1Usz3+aKCsykcAv4qgAIPYX46jKjHk4IV5Ayk+PmCjdwocGT0jEhXnxaWlVhD5c+pOumVaEv5HKNLqXZ07eaBK6/Jd2imxasI7tWS6BlkOH4YoyVm7o+O9BTyNNXKskSXeC8bPe6UACxqE4Dud1LJjFdoxt1QGCmInpsw2qncmBbJLtsV2bl8jZbgZv3Jp5sDwAXb9d/ISB2ZvLnxICfqDwGA2M9AwMTM3Dt71DKnP59TiajlLx02DPGBnHJvAokkr1KD+lhDa8ILeTp6p+1aVvUVfF2788sjBXLZ9KrZaluD7GcK9eyiZalpcu5p2vXK+CGtofITWZXiR6328tlLjuP6zIOx47he0B/uCz80xy7UY8h+iNvo5yrUk5Hj+naj89Yx6sDruu5I4vplqe+eK+/gYxH2lhepRtzPh7XaN6tzhGcS5+isVetQ9AULi+n/p2d935rQNwGzR7OVr6BeMRZ+HegYxyi+HyIMPF9zt3UIewAbSOj0OohaVSmlWy5ea8MAcH2ePyd/XAmQKoohZYYJIld4T5kV0leqh/8jfEB78ak4VBmyr6olsmhLKdWQ+QfRHPcZ6GGUcbHcbdJvt3jQUTnwLP0l+DobWvP3A8/CffebWzfd67G32dfqi9nF133b3Nuz2sGt7s3gxDzeJpuXA8+IGPIojR89aDxMyqxYKLNfG88dvjAubkOxlAMtycLL05vDwNoilQADLyP5qcLD3vXOw93EOJ4X7z70IjwYL50AIF12irctNt8y1+47VugOi3pDtu0LcXcACbJOXQxTzkBe7nDfAyg8RKxln6HjNiGOMQbuZ8vvi8SgLFCngUyNrxXJbQwpXaisvSvAT8oqxV7GusfR+AXF+tVRwIPB4tpRtJHB68SvCS6kxcd87I1dLAwkWzc3vMuJT+sqwf8kLSfIJo+J9A+++vIT307hAihX4IE+Y7vGCHDrHSfzJ9pF/k74D7jqvjPcWGmq1zM1iq3N3TY34Bo/jBVvdEhEZdnDzNbYuvlEgzYP2qmfjg0ghjrqmTdzfkenroTWZN/bXae7KBCFEZpMkRGq9Nndm7I8Mo6HlomB4xSijdTBA+yc9QTagamM+wMsv2ZQm6K0mJAf3R4b1euREB2jPa6dHaunPf3yTYTyU9B8g6BL3UvuBlMBnxhFRW4Achz4Tw+O5qHtB6+Jo8cYLrPeDE7jnLT1T/wdnM2g0g4P7+RouDeEKLpPukOL5Gsj5Cstm6RrlsxrJbj7GuIyMZi0JCbGF64OZGzvnbIXzjq4623FElXSttwJJ7Z652duVBEuFrHXF7mwtCzCA9qX8FC5uyta1b4+sER4/yciuMVCSUNQ+UsqB3/PrtW8Ug6Bu50ew/8DbSOBU0Jjg9ODK4L5pGBaxZJD6IxTNqPFClsDzzgpSTGBIyAU9z35TIIB0dMgGQLXPxiwIRdh44OHgtWAjTwYyjAeOt70pWZpDBEeGSd/MNHLn/qAq9FB46fy7DLqSlKVIu4jtQF7zHDrq1dhmUCR9Yd7ir1j2PzBXvy4SLbrdM4m3s6VKCT9s5iG8TV07aK9hn3MtT+k4a+yFZFNaNAFg2Z1Z/xHndH5gESAOj1JTd29429QCxPjUDTKvB7rVPc/G/K686gUv8SHyvcIMjwVeXEknB8HwgEtqCxp/yuyumd0aCDX3Ssma0FjfBW3mC98PY/MSXdGvKJ80GU/gi+pD7a+K7UPs9ZVp3CXeHj4q1ZYap96qB0wXWFwD+5yrmKu1esfZwIUAhT/0QgqtLrJkOFP/cJSmhrRcRDHfwZB/7BAHvFLjcDecJn0r8QHzgECt2m/QvzG4S5U7wzvmsdjOInA3yIXR4pc40IDDKUT6bz2YvXJBDpi94zvoMKiwfQ/Vdr0cc1uttpauLcdO3n07egy94LpTfVrZ03nLHSXZDZZiBKvwHpn0EJZuNpZ4CjR7KMYo3oJRI9wuDNXGOFFo/gDfEvQBPwcuARnt9B4B/RdZn8HSFP6+AMAhbYB2+6DWgX0veFSi4PMmsvsWIpka8EMiMVU6sQuU4p5yOtPGgrVH+2A2e7EqEn0KN65GylrbsscCPz4eUKUvYunuzILOQupCiVrvEg0eAd8WCx2zPQxMqgaf8t/xCgfV4xFF2VqPEskb1yJgCjbVkNUaHyk85kqYjqvl4gU+D6T8vrOsTJmu7iLmUoa+gfylsnECk2Ospd1kIimDuKOyzxKTrjSCKgu5vB+P46P+7b6VePHWHcEjxiC9CAnd0sSPBdAS6Exzq47t4+Tzhk6CzB+CAaYBXASzYNEn7i3ho1pJ+LuukeXGBeruOvHtyZfC6qXS/gtmpkEWBcJujvbMHPGjMoX4wMLexFchjYXZ6SJMopXvthzL4YtDAysmSUb5xRcGXwOnCTIug7AHulfZg9y1uU1z2nQ6xuhFnLE6tdBA6wbL8a/FUekOygHAHEAQgi8AMB7oKbuihTCq/6GFtEG1AjfruBzu5P1r1+7zzr3jFlg2DXKteYgRb1OteGI/NZQzRCiT6JOdGy5HXCmXzUeom9IRnEC+gW0HTQTa8+v2Y4uGtBlg8GRAFJUs+EsFlaBOwvnZiZiICVPLXbZ/RKVT0ouXRY4LPeUoLGvQv4qVMvKohjUBl2csq6jH8eeFT7kKEW+DQEjnsXwSr/PEOrP5NBey8BveBImrpfPZrvnrhCuLzxRUwF7eGyeMP94bhJNMGc6LQtP346lUQzeLw1VUl0q0OACYHbIBu7knF2je2g46oXo5b9LwGlDCd+nNA3ERf3DApB/j245LHrmdIBgNykMBave++d7z7UDGbyzemQErjZzXDuE4UqBYUH8HaFMBWk5vg/f9uMt3CF/YBCSe6hLL4S7t8BTAHorDKmq89GX3rshqUgR8MQ+3t+1X/aYKT7X36f0B0MMvOZwC/KZsdWpOxe5WaZukAe/GkW4dTvlHr2uTbgpqqEPwz4DK7TXLgAf8vF0tG5iOg8wZFBPoX7Eu/AvlnUh4S9L+j1y/XbteHb8T/pG89VJL8j87KoiroFOuIDtK0qb4HcxDJoC3vVTCU7FVHVYr4LhpfwdZnVWm3T7MSjNwSQhCcEgQXB209T+CyLBVlFpYI+Z421IBn6bJF117W+nTASJsk9Uv+gJeR3IcjcW/lGQwE+zeXsm8wVFgyjDGTyp8xr1Jt26P1u07AKhhf5CdC4UrwFew1w/fwhjHFDqDPgBU/EdcTRXjDoxViE6gW/7Jktfd1Bz7J7MT3A+ajt9+SLM2EGj8fSrb47CkPWt8NqPnLpwfLoHGEZPSql6EXCn5wINbA/g1BfvUrvq0Iw7vHP52hcRL7Mch1TYpHFQt/UCaALmp36ev6AAh/dDHkn46kQMslKFeK8DY2HtyD5JiMMfyQcn0SmkdJCwXOQyWDS1xq9t1mtF4Ubr/l2AJcvvLCWizbd0lVL48n1eURzBtci3kbAPhKDBnO0wzOQYlUAwHFZRprbU3GY7euiGqladlK6jWFCQgpsZ1ycvfZGaT4CSgdrfj139K2HdGjnXVu9De5GfvybISuM3QMbSYPn4qKeE9TgBY7nz+gUwvrWLyV7vXgWVVgKOqITWd965N6T6nQw5ra80FfyJBrUAP0jQpTNs1b3iOVQD17fg7y26p5INxezZec+lGzxZCgRe27qidghgvie4RmHxZy9QNakL+vsvLXSkUH8rjmNyDHqEkYfqMmnJtOKh9ttQy8U8RJM151/M9XPXJQDI/L4okGXRYK3Z7kdeJYVaBndrZzhpIxMo5whPRcPiXc1IJMS10NW+IXhNK5y1L65SvbCxOxyRI4JtjCdTE+ddeT4hlSwzK0Jy+rNWqS6OTmOURjjHd1g/tJxi2cGr81fJeTG2P/qzDkuqeG+4vvhzOzywhbywpkP92n4DroF1jBNgXaMM3zN5ATaPU1RjEIVvbTvaogUIG2a4QjyFfrZnXUa4c41FCG6J2HLqSAq1i1gyIq4RLvaRc2BnzqO/HJwYSdHELfZWz5mKbzm0dJRYDp0HXDRnyO01nTCL/60p6Rl9sPUtsIPG1jfVZ1wCDUu53wc4PR8czU50gO94YMw7pqHJ1Lr0/0AXd0HvW+1y2L8OZulVfZ+QKpvcWJm9uF8rCEquI3h0FL8HO6QWfBxxr10o+MC0WBMuCplb42yLWznaStS9jm/qpPbEoQ9cn8xba2s3F5siCLxPn9nF4FnO2FBISr4Pe3ySX7FE2BQUeMj5LTTXFWZ4EpwOeQEI1dN+2w/VXspYrZDvZbK+JCrarpurB/jMZn7Y0Lb1Q4YTGp14Y26g9/lE0ny2T2l9HAk64tfVhFx5/JopmjS3g/NMPXUxU0AUoU1GGYiYEJwEFTyujxkMrQoGxit4NJbtPlitQVip9pRRBrXCWtYcZtzKiPwZoW5KvYQe0I+XvjKAPOk8pz5t12GT07Zb2u0R8o3cvOqv1P/kjudpwjz4QEKtFJ3eWDJH2kVvrnzpA9TEPz9kz4BTKhQyCwuwxY4Y9DfO7jGnROweRmx9znGAVK0x3sxIg+3bxpmFGQL2cAas9QgisII3xvoDmZciEurOC6JgCdf9pRyIclYDkvwZA4rah1r6a5ZGV/lNzEZKjdpPjzvlsSZEB/PZW/KjzjsmBbH9aA17U4oslZRTumzhJ7HVXie7VOjipr7sonMRcoXsLPow4mGTpGMlui8oP6U5RKIO0W2itdjEsh11OkGtNbQFmbgUaF4P8R6SPWS5mwEmqB4CybR6MuwfTH3eAHaRSqFqkzag/lUcumWuuUR7JJiGZb1Q1nnwCtm1wPwHONcPi8Q5HRJuFX+4Q8GZaK/Xg0mEGl+tz28yU2fnZvVuKa5FDPGp/Y7E1lNo8ZCtxcl2L6K4fl09gXDJZCZTcQjeBUuAFWhICfBr/TnKTbkc6JPwScG7L3yYKViKivGhyAfaISUgNxVEdMW7DhTBziZ/fhSQoPXaHIAMaBpi+yp03MTfLS8AVaWCXKU2o/ZxdRwqDl7Y3fw6lYNMlhwC8sukPTZ8qsGILbqq44PDHtdYBSxMb5m7Q7llJAiAhYAJfamsNAlvQJt//pkpj5LyDuVCQpoFCcE9PwJsGqnZSpnjvqEDuZBvFILIPgLe4ic2W9XCIwkrQqSKJArNyVJ9AovRSlX1Fednw6UE5tG0qzzQN6YEsjZV2X4ku8rDjTKw6Ag9WhWsx2UIpjN1Y1EbEVwH1qZcQqMqRTkBt5NJ7AqCzaUP6W0F+Z1BoNNlhfay+i99O/L0tMTgCIjzcY7eaqMlspS9IeE9M+3uLA4FMIzdWCYIsse0JwqCDO9Njpj7UGIIoWQICro4Uzceg7PmejP12D83fJSzhdxxmZeRv4BDjg9B4+IM2/b2NhY+3uOo5yPTdvSUwMNcr+CtM52BVyYK9OXTDmt14TM8YQiXpsEjGt+cVi/kveiQ3M6b5fH9kP4nMLdzZ3F++hquPkAipkYOZVmPjPq68H4pChFK4w6C/4ONbkQbAxq5+ZJAt5fKLkf6cOkKk38ovsQ458EX9ov8PzN2AvBwwRrb9/hNMPawdL3vw70q1k+3r3H6u/SdTo36wnc9dCbw8THop9Id7TBe41jCNq4Q/r+FE7OvBfTigW82Tm2GL0pucx2JlCKbD2QOynMZifOMZoLIuqs+bDjxuB6MsQMwWILIhqsjdADxibmTMhcwIUYa4UK5qbVSA8EsOYrhEnNFZ3irtBpX+nYIPR8ta1QB4f0BvQ70diUX2Ggi/fz+ttGoeE46tGvZJ86kVVnQoEeakMLacelZZw+kQGiIlidZi5y5zG90eFVvUs5eI+KAZOssAhZFchi0fjvKdpBeoPmj38Al3ZfsDZC48Hcy6tkk1piJXESMkkjvYY1HccRvs5LLkkLXSzK+YbmkKGCuLsuEpVaOHnQsLbpz7Hu+3wOCppC3PSUwifDygHvidpgMNfvg7tbk01wnArQxaH422G4Wc7xpMJkP+Rc4iY5zLMlPP3JrhS55SLbKhFJEfxc76tnXRg8htEQy/nuLD4Kr9Ms6WX40yy2LfyJCTWGOD/pkmDnq0tfckl7Owxw38m2wAcvSpL0AeVyw3HPlXty7tU3QzrkC39UfiBMmG1OvyY4w+GeWCNTws0UhS1Sz2RsM7KqAAeABmqXcfKFJyz6dZNgw6tbR6o471U1Ui9iaBlWrGR2ab/569MW1vJzFsU4RFfyTdiW9xbCCRfxym1qa8TgPGkV3E7TgTWKIsoDMZUSxThiOAaOXsQiiyJMGXaOdsotX196
*/