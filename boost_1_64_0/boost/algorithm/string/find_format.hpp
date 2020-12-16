//  Boost string_algo library find_format.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_HPP
#define BOOST_STRING_FIND_FORMAT_HPP

#include <deque>
#include <boost/detail/iterator.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/concept.hpp>
#include <boost/algorithm/string/detail/find_format.hpp>
#include <boost/algorithm/string/detail/find_format_all.hpp>

/*! \file
    Defines generic replace algorithms. Each algorithm replaces
    part(s) of the input. The part to be replaced is looked up using a Finder object.
    Result of finding is then used by a Formatter object to generate the replacement.
*/

namespace boost {
    namespace algorithm {

// generic replace  -----------------------------------------------------------------//

        //! Generic replace algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
    
            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_copy_impl(
                Output,
                lit_input,
                Formatter,
                Finder( ::boost::begin(lit_input), ::boost::end(lit_input) ) );
        }

        //! Generic replace algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT>
        inline SequenceT find_format_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_copy_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }

        //! Generic replace algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. The input is modified in-place.

            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
        */
        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT>
        inline void find_format( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }


//  find_format_all generic ----------------------------------------------------------------//

        //! Generic replace all algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. Repeat this for all matching
            substrings.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_all_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT(( 
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_all_copy_impl(
                Output,
                lit_input,
                Finder,
                Formatter,
                Finder(::boost::begin(lit_input), ::boost::end(lit_input)));
        }

        //! Generic replace all algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT >
        inline SequenceT find_format_all_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_all_copy_impl(
                Input,
                Finder,
                Formatter,
                Finder( ::boost::begin(Input), ::boost::end(Input) ) );
        }

        //! Generic replace all algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. Repeat this for all matching
            substrings.The input is modified in-place.

            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
        */
        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT >
        inline void find_format_all( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_all_impl(
                Input,
                Finder,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));

        }

    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::find_format_copy;
    using algorithm::find_format;
    using algorithm::find_format_all_copy;
    using algorithm::find_format_all;

} // namespace boost


#endif  // BOOST_STRING_FIND_FORMAT_HPP

/* find_format.hpp
fuEx6hNspi+k5rOLx+t03DuZ/h9yyo5/qto9sJLjP6zMeKzi3+H8r+Cn9YjBZ2Kx5rII/jfHmPC1nzfhXXdF8n9q4d+xRMNnR8Ifa+F/yIR/MT+S/9OpJv6v7zH9314ayf/pVMt/qwnfLxJ+n4X/xN2m/9tI+DMs/DtM+MOLIvk/tfB7l2v45Ej4v5pi4j/PhF8cCf9aEz6+m1/D7+4UAT7Pwl/LhG8fCf9gC/9H92r4SZHwt7TwP2/C7wI5OfX6n2zif2OZho+LhH+zCV/7bhN+YiT8y0P4/eb67xhp/Yfwm/CuSPg7aXhjD4psM5f0U1Sk4vVvtcda/4mR2rNvktmeW0z4uXdWDC/+bwWepEIkp70MhdTuSy0fpuXXv4bHejDxvzQv0vq34K3xmR8JPt6Cf97cL/0jwX810YQ/cZeGbxYJfq0F3y1fw383N9L6t+DfMOnbxkjwgy34j0z8SyPBt7Tgn1+s4a+PBP/TrVZ7zPHvEAl+swX/tTk+jkjwy0342LYmPSyYE2n9W/DPGxp+UST4Thb8DrM9QyPBx1rw55njmRQJft8EE/6ahRr+6OxI9N+C/8gc/62R4H0WvEUPTyZHWv8W/A6zPWMj4Y+34B8y8adGgv/qFmv8zflyRoJfa8F/tEjDfxBSu6/I33/uLWbsHNZZ2uvrCL7UiWPKjEzXeJmIe0eTuHchi3ubsbh36NCQ1//CjvzatRXiX+gpfsGJgacn65or9T6TyOt/PLdGhN2kWpOXZan+dOaYPmw6MjCbX7CaFqZwtdvxUoNq96iUyXZ3ofzE1Ge65XeTbpepHrLjryxTdir/n+Nt/Lc/u566saMYeNUOZxTzDkLW0Sde1byeO1F4idnaXWjtezZWfdak37ywldM3e/tmaYS8Yo2z3qlY6ezGpTJp54pJrjllTw+pSONL3ZEpNwj/QCfapv40k35uz48p/DOKm9HqdpYpFtgy8TcbXZH/b2k2o1YXp1izm5KbGue7mBXPifkmTWB1yEMN2cpRs0lsnrIt3YhSiWieiIVFJF05+VCk+Clzx+lVV8qxflKC6uvMMD/b5yyR4Uxlp2LT/P0wnL3dashg1m19kMfHqSZBFoMnw/NH8CsUPH50VddmhC4FPdSSsZapaAdZyDWRgl/NIeA24584i6OiCSELVtCUHzysDdiR3ERxI7JFFzR3MakFr8ZKelu9M0iCAyV3kReY166wmUv8e0KbaPo/NvSe3iVM/p8G65ZUln+OtQcrpc5ESaST6so1ghWMH8algHe5x7JYq0YMC8RBrLeiNg23ZiebRqSbBLN7FiSy0LBRqFcHEhwpmhTcGMOvsncChFAbs2WgdqVZXqXNGozeqRx1jf0UA7lXdGtmT+Db3hrWPHGvi9UKt0m5bwetF3a/O0atmsNXxkQ2sEel3CDip+6h6bof01U7MIrcxf6V56xfAgd5xO5T7SE7gIiUG8xqOFeww46N2l12cg/RToLyruUr4zU/SW37oRq1DmSehX3WqKbspWI/zpBiP56UYkNRbB4XG0jFtrWhBWrW+B6AGImu8zVd+DWkn6LjDrPjj83mjtdmzXWgDkSjoezr5HJSIGCk6Cm6jPB13fSwm/fa1H+nqK9Sf5r/GaPX88ZkiU8It21h57+Vn8D5VSm/Ynp9rgbl6IUqp4es8XeHWUu5Bi9lOrgmk6OA6Gt4MyyZLIBXgJJY0ZR6AootQrKg1SHHLuKETVRreee4SPUYFK4pj255/d53VfEsQfYxIbuSiTyt4MLZOs64QWv1KXVbtuyS6kDLaFI2nDWdYL6ShPQ3y3q3/qxgEfM/o0xigcc02pBZ1dKNz/BxxDiA//+ZbnyHDxc=
*/