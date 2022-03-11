//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_BOUNDARY_INDEX_HPP_INCLUDED
#define BOOST_LOCALE_BOUNDARY_INDEX_HPP_INCLUDED

#include <boost/locale/config.hpp>
#include <boost/locale/boundary/types.hpp>
#include <boost/locale/boundary/facets.hpp>
#include <boost/locale/boundary/segment.hpp>
#include <boost/locale/boundary/boundary_point.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <string>
#include <locale>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

#include <iostream>

namespace boost {

    namespace locale {
        
        namespace boundary {
            ///
            /// \defgroup boundary Boundary Analysis
            ///
            /// This module contains all operations required for %boundary analysis of text: character, word, like and sentence boundaries
            ///
            /// @{
            ///

            /// \cond INTERNAL

            namespace details {

                template<typename IteratorType,typename CategoryType = typename std::iterator_traits<IteratorType>::iterator_category>
                struct mapping_traits {
                    typedef typename std::iterator_traits<IteratorType>::value_type char_type;
                    static index_type map(boundary_type t,IteratorType b,IteratorType e,std::locale const &l)
                    {
                        std::basic_string<char_type> str(b,e);
                        return std::use_facet<boundary_indexing<char_type> >(l).map(t,str.c_str(),str.c_str()+str.size());
                    }
                };

                template<typename CharType,typename SomeIteratorType>
                struct linear_iterator_traits {
                    static const bool is_linear =
                        is_same<SomeIteratorType,CharType*>::value
                        || is_same<SomeIteratorType,CharType const*>::value
                        || is_same<SomeIteratorType,typename std::basic_string<CharType>::iterator>::value
                        || is_same<SomeIteratorType,typename std::basic_string<CharType>::const_iterator>::value
                        || is_same<SomeIteratorType,typename std::vector<CharType>::iterator>::value
                        || is_same<SomeIteratorType,typename std::vector<CharType>::const_iterator>::value
                        ;
                };



                template<typename IteratorType>
                struct mapping_traits<IteratorType,std::random_access_iterator_tag> {

                    typedef typename std::iterator_traits<IteratorType>::value_type char_type;



                    static index_type map(boundary_type t,IteratorType b,IteratorType e,std::locale const &l)
                    {
                        index_type result;

                        //
                        // Optimize for most common cases
                        //
                        // C++0x requires that string is continious in memory and all known
                        // string implementations
                        // do this because of c_str() support. 
                        //

                        if(linear_iterator_traits<char_type,IteratorType>::is_linear && b!=e)
                        {
                            char_type const *begin = &*b;
                            char_type const *end = begin + (e-b);
                            index_type tmp=std::use_facet<boundary_indexing<char_type> >(l).map(t,begin,end);
                            result.swap(tmp);
                        }
                        else {
                            std::basic_string<char_type> str(b,e);
                            index_type tmp = std::use_facet<boundary_indexing<char_type> >(l).map(t,str.c_str(),str.c_str()+str.size());
                            result.swap(tmp);
                        }
                        return result;
                    }
                };

                template<typename BaseIterator>
                class mapping {
                public:
                    typedef BaseIterator base_iterator;
                    typedef typename std::iterator_traits<base_iterator>::value_type char_type;


                    mapping(boundary_type type,
                            base_iterator begin,
                            base_iterator end,
                            std::locale const &loc) 
                        :   
                            index_(new index_type()),
                            begin_(begin),
                            end_(end)
                    {
                        index_type idx=details::mapping_traits<base_iterator>::map(type,begin,end,loc);
                        index_->swap(idx);
                    }

                    mapping()
                    {
                    }

                    index_type const &index() const
                    {
                        return *index_;
                    }

                    base_iterator begin() const
                    {
                        return begin_;
                    }

                    base_iterator end() const
                    {
                        return end_;
                    }

                private:
                    boost::shared_ptr<index_type> index_;
                    base_iterator begin_,end_;
                };

                template<typename BaseIterator>
                class segment_index_iterator : 
                    public boost::iterator_facade<
                        segment_index_iterator<BaseIterator>,
                        segment<BaseIterator>,
                        boost::bidirectional_traversal_tag,
                        segment<BaseIterator> const &
                    >
                {
                public:
                    typedef BaseIterator base_iterator;
                    typedef mapping<base_iterator> mapping_type;
                    typedef segment<base_iterator> segment_type;
                    
                    segment_index_iterator() : current_(0,0),map_(0)
                    {
                    }

                    segment_index_iterator(base_iterator p,mapping_type const *map,rule_type mask,bool full_select) :
                        map_(map),
                        mask_(mask),
                        full_select_(full_select)
                    {
                        set(p);
                    }
                    segment_index_iterator(bool is_begin,mapping_type const *map,rule_type mask,bool full_select) :
                        map_(map),
                        mask_(mask),
                        full_select_(full_select)
                    {
                        if(is_begin)
                            set_begin();
                        else
                            set_end();
                    }

                    segment_type const &dereference() const
                    {
                        return value_;
                    }

                    bool equal(segment_index_iterator const &other) const
                    {
                        return map_ == other.map_ && current_.second == other.current_.second;
                    }

                    void increment()
                    {
                        std::pair<size_t,size_t> next = current_;
                        if(full_select_) {
                            next.first = next.second;
                            while(next.second < size()) {
                                next.second++;
                                if(valid_offset(next.second))
                                    break;
                            }
                            if(next.second == size())
                                next.first = next.second - 1;
                        }
                        else {
                            while(next.second < size()) {
                                next.first = next.second;
                                next.second++;
                                if(valid_offset(next.second))
                                    break;
                            }
                        }
                        update_current(next);
                    }

                    void decrement()
                    {
                        std::pair<size_t,size_t> next = current_;
                        if(full_select_) {
                            while(next.second >1) {
                                next.second--;
                                if(valid_offset(next.second))
                                    break;
                            }
                            next.first = next.second;
                            while(next.first >0) {
                                next.first--;
                                if(valid_offset(next.first))
                                    break;
                            }
                        }
                        else {
                            while(next.second >1) {
                                next.second--;
                                if(valid_offset(next.second))
                                    break;
                            }
                            next.first = next.second - 1;
                        }
                        update_current(next);
                    }

                private:

                    void set_end()
                    {
                        current_.first  = size() - 1;
                        current_.second = size();
                        value_ = segment_type(map_->end(),map_->end(),0);
                    }
                    void set_begin()
                    {
                        current_.first = current_.second = 0;
                        value_ = segment_type(map_->begin(),map_->begin(),0);
                        increment();
                    }

                    void set(base_iterator p)
                    {
                        size_t dist=std::distance(map_->begin(),p);
                        index_type::const_iterator b=map_->index().begin(),e=map_->index().end();
                        index_type::const_iterator 
                            boundary_point=std::upper_bound(b,e,break_info(dist));
                        while(boundary_point != e && (boundary_point->rule & mask_)==0)
                            boundary_point++;

                        current_.first = current_.second = boundary_point - b;
                        
                        if(full_select_) {
                            while(current_.first > 0) {
                                current_.first --;
                                if(valid_offset(current_.first))
                                    break;
                            }
                        }
                        else {
                            if(current_.first > 0)
                                current_.first --;
                        }
                        value_.first = map_->begin();
                        std::advance(value_.first,get_offset(current_.first));
                        value_.second = value_.first;
                        std::advance(value_.second,get_offset(current_.second) - get_offset(current_.first));

                        update_rule();
                    }

                    void update_current(std::pair<size_t,size_t> pos)
                    {
                        std::ptrdiff_t first_diff = get_offset(pos.first) - get_offset(current_.first);
                        std::ptrdiff_t second_diff = get_offset(pos.second) - get_offset(current_.second);
                        std::advance(value_.first,first_diff);
                        std::advance(value_.second,second_diff);
                        current_ = pos;
                        update_rule();
                    }

                    void update_rule()
                    {
                        if(current_.second != size()) {
                            value_.rule(index()[current_.second].rule);
                        }
                    }
                    size_t get_offset(size_t ind) const
                    {
                        if(ind == size())
                            return index().back().offset;
                        return index()[ind].offset;
                    }

                    bool valid_offset(size_t offset) const
                    {
                        return  offset == 0 
                                || offset == size() // make sure we not acess index[size]
                                || (index()[offset].rule & mask_)!=0;
                    }
                    
                    size_t size() const
                    {
                        return index().size();
                    }
                    
                    index_type const &index() const
                    {
                        return map_->index();
                    }
                
                    
                    segment_type value_;
                    std::pair<size_t,size_t> current_;
                    mapping_type const *map_;
                    rule_type mask_;
                    bool full_select_;
                };
                            
                template<typename BaseIterator>
                class boundary_point_index_iterator : 
                    public boost::iterator_facade<
                        boundary_point_index_iterator<BaseIterator>,
                        boundary_point<BaseIterator>,
                        boost::bidirectional_traversal_tag,
                        boundary_point<BaseIterator> const &
                    >
                {
                public:
                    typedef BaseIterator base_iterator;
                    typedef mapping<base_iterator> mapping_type;
                    typedef boundary_point<base_iterator> boundary_point_type;
                    
                    boundary_point_index_iterator() : current_(0),map_(0)
                    {
                    }

                    boundary_point_index_iterator(bool is_begin,mapping_type const *map,rule_type mask) :
                        map_(map),
                        mask_(mask)
                    {
                        if(is_begin)
                            set_begin();
                        else
                            set_end();
                    }
                    boundary_point_index_iterator(base_iterator p,mapping_type const *map,rule_type mask) :
                        map_(map),
                        mask_(mask)
                    {
                        set(p);
                    }

                    boundary_point_type const &dereference() const
                    {
                        return value_;
                    }

                    bool equal(boundary_point_index_iterator const &other) const
                    {
                        return map_ == other.map_ && current_ == other.current_;
                    }

                    void increment()
                    {
                        size_t next = current_;
                        while(next < size()) {
                            next++;
                            if(valid_offset(next))
                                break;
                        }
                        update_current(next);
                    }

                    void decrement()
                    {
                        size_t next = current_;
                        while(next>0) {
                            next--;
                            if(valid_offset(next))
                                break;
                        }
                        update_current(next);
                    }

                private:
                    void set_end()
                    {
                        current_ = size();
                        value_ = boundary_point_type(map_->end(),0);
                    }
                    void set_begin()
                    {
                        current_ = 0;
                        value_ = boundary_point_type(map_->begin(),0);
                    }

                    void set(base_iterator p)
                    {
                        size_t dist =  std::distance(map_->begin(),p);

                        index_type::const_iterator b=index().begin();
                        index_type::const_iterator e=index().end();
                        index_type::const_iterator ptr = std::lower_bound(b,e,break_info(dist));

                        if(ptr==index().end())
                            current_=size()-1;
                        else
                            current_=ptr - index().begin();

                        while(!valid_offset(current_))
                            current_ ++;

                        std::ptrdiff_t diff = get_offset(current_) - dist;
                        std::advance(p,diff);
                        value_.iterator(p);
                        update_rule();
                    }

                    void update_current(size_t pos)
                    {
                        std::ptrdiff_t diff = get_offset(pos) - get_offset(current_);
                        base_iterator i=value_.iterator();
                        std::advance(i,diff);
                        current_ = pos;
                        value_.iterator(i);
                        update_rule();
                    }

                    void update_rule()
                    {
                        if(current_ != size()) {
                            value_.rule(index()[current_].rule);
                        }
                    }
                    size_t get_offset(size_t ind) const
                    {
                        if(ind == size())
                            return index().back().offset;
                        return index()[ind].offset;
                    }

                    bool valid_offset(size_t offset) const
                    {
                        return  offset == 0 
                                || offset + 1 >= size() // last and first are always valid regardless of mark
                                || (index()[offset].rule & mask_)!=0;
                    }
                    
                    size_t size() const
                    {
                        return index().size();
                    }
                    
                    index_type const &index() const
                    {
                        return map_->index();
                    }
                
                    
                    boundary_point_type value_;
                    size_t current_;
                    mapping_type const *map_;
                    rule_type mask_;
                };


            } // details

            /// \endcond

            template<typename BaseIterator>
            class segment_index;

            template<typename BaseIterator>
            class boundary_point_index;
            

            ///
            /// \brief This class holds an index of segments in the text range and allows to iterate over them 
            ///
            /// This class is provides \ref begin() and \ref end() member functions that return bidirectional iterators
            /// to the \ref segment objects.
            ///
            /// It provides two options on way of selecting segments:
            ///
            /// -   \ref rule(rule_type mask) - a mask that allows to select only specific types of segments according to
            ///     various masks %as \ref word_any.
            ///     \n
            ///     The default is to select any types of boundaries.
            ///     \n 
            ///     For example: using word %boundary analysis, when the provided mask is \ref word_kana then the iterators
            ///     would iterate only over the words containing Kana letters and \ref word_any would select all types of
            ///     words excluding ranges that consist of white space and punctuation marks. So iterating over the text
            ///     "to be or not to be?" with \ref word_any rule would return segments "to", "be", "or", "not", "to", "be", instead
            ///     of default "to", " ", "be", " ", "or", " ", "not", " ", "to", " ", "be", "?".
            /// -   \ref full_select(bool how) - a flag that defines the way a range is selected if the rule of the previous
            ///     %boundary point does not fit the selected rule.
            ///     \n
            ///     For example: We want to fetch all sentences from the following text: "Hello! How\nare you?".
            ///     \n
            ///     This text contains three %boundary points separating it to sentences by different rules:
            ///     - The exclamation mark "!" ends the sentence "Hello!"
            ///     - The line feed that splits the sentence "How\nare you?" into two parts.
            ///     - The question mark that ends the second sentence.
            ///     \n
            ///     If you would only change the \ref rule() to \ref sentence_term then the segment_index would
            ///     provide two sentences "Hello!" and "are you?" %as only them actually terminated with required
            ///     terminator "!" or "?". But changing \ref full_select() to true, the selected segment would include
            ///     all the text up to previous valid %boundary point and would return two expected sentences:
            ///     "Hello!" and "How\nare you?".
            ///     
            /// This class allows to find a segment according to the given iterator in range using \ref find() member
            /// function.
            ///
            /// \note
            ///
            /// -   Changing any of the options - \ref rule() or \ref full_select() and of course re-indexing the text
            ///     invalidates existing iterators and they can't be used any more.
            /// -   segment_index can be created from boundary_point_index or other segment_index that was created with
            ///     same \ref boundary_type.  This is very fast operation %as they shared same index
            ///     and it does not require its regeneration.
            ///
            /// \see
            ///
            /// - \ref boundary_point_index
            /// - \ref segment
            /// - \ref boundary_point
            ///

            template<typename BaseIterator>
            class segment_index {
            public:
                
                ///
                /// The type of the iterator used to iterate over the original text
                ///
                typedef BaseIterator base_iterator;
                #ifdef BOOST_LOCALE_DOXYGEN
                ///
                /// The bidirectional iterator that iterates over \ref value_type objects.
                ///
                /// -   The iterators may be invalidated by use of any non-const member function
                ///     including but not limited to \ref rule(rule_type) and \ref full_select(bool).
                /// -   The returned value_type object is valid %as long %as iterator points to it.
                ///     So this following code is wrong %as t used after p was updated:
                ///     \code
                ///     segment_index<some_iterator>::iterator p=index.begin();
                ///     segment<some_iterator> &t = *p;
                ///     ++p;
                ///     cout << t.str() << endl;
                ///     \endcode
                ///
                typedef unspecified_iterator_type iterator;
                ///
                /// \copydoc iterator
                ///
                typedef unspecified_iterator_type const_iterator;
                #else
                typedef details::segment_index_iterator<base_iterator> iterator;
                typedef details::segment_index_iterator<base_iterator> const_iterator;
                #endif
                ///
                /// The type dereferenced by the \ref iterator and \ref const_iterator. It is
                /// an object that represents selected segment.
                ///
                typedef segment<base_iterator> value_type;

                ///
                /// Default constructor. 
                ///
                /// \note
                ///
                /// When this object is constructed by default it does not include a valid index, thus
                /// calling \ref begin(), \ref end() or \ref find() member functions would lead to undefined
                /// behavior
                ///
                segment_index() : mask_(0xFFFFFFFFu),full_select_(false)
                {
                }
                ///
                /// Create a segment_index for %boundary analysis \ref boundary_type "type" of the text
                /// in range [begin,end) using a rule \a mask for locale \a loc.
                ///
                segment_index(boundary_type type,
                            base_iterator begin,
                            base_iterator end,
                            rule_type mask,
                            std::locale const &loc=std::locale()) 
                    :
                        map_(type,begin,end,loc),
                        mask_(mask),
                        full_select_(false)
                {
                }
                ///
                /// Create a segment_index for %boundary analysis \ref boundary_type "type" of the text
                /// in range [begin,end) selecting all possible segments (full mask) for locale \a loc.
                ///
                segment_index(boundary_type type,
                            base_iterator begin,
                            base_iterator end,
                            std::locale const &loc=std::locale()) 
                    :
                        map_(type,begin,end,loc),
                        mask_(0xFFFFFFFFu),
                        full_select_(false)
                {
                }

                ///
                /// Create a segment_index from a \ref boundary_point_index. It copies all indexing information
                /// and used default rule (all possible segments)
                ///
                /// This operation is very cheap, so if you use boundary_point_index and segment_index on same text
                /// range it is much better to create one from another rather then indexing the same
                /// range twice.
                ///
                /// \note \ref rule() flags are not copied
                ///
                segment_index(boundary_point_index<base_iterator> const &);
                ///
                /// Copy an index from a \ref boundary_point_index. It copies all indexing information
                /// and uses the default rule (all possible segments)
                ///
                /// This operation is very cheap, so if you use boundary_point_index and segment_index on same text
                /// range it is much better to create one from another rather then indexing the same
                /// range twice.
                ///
                /// \note \ref rule() flags are not copied
                ///
                segment_index const &operator = (boundary_point_index<base_iterator> const &);

                
                ///
                /// Create a new index for %boundary analysis \ref boundary_type "type" of the text
                /// in range [begin,end) for locale \a loc.
                ///
                /// \note \ref rule() and \ref full_select() remain unchanged.
                ///
                void map(boundary_type type,base_iterator begin,base_iterator end,std::locale const &loc=std::locale())
                {
                    map_ = mapping_type(type,begin,end,loc);
                }

                ///
                /// Get the \ref iterator on the beginning of the segments range.
                ///
                /// Preconditions: the segment_index should have a mapping
                ///
                /// \note
                ///
                /// The returned iterator is invalidated by access to any non-const member functions of this object
                ///
                iterator begin() const
                {
                    return iterator(true,&map_,mask_,full_select_);
                }

                ///
                /// Get the \ref iterator on the ending of the segments range.
                ///
                /// Preconditions: the segment_index should have a mapping
                ///
                /// The returned iterator is invalidated by access to any non-const member functions of this object
                ///
                iterator end() const
                {
                    return iterator(false,&map_,mask_,full_select_);
                }

                ///
                /// Find a first valid segment following a position \a p. 
                ///
                /// If \a p is inside a valid segment this segment is selected:
                ///
                /// For example: For \ref word %boundary analysis with \ref word_any rule():
                ///
                /// - "to| be or ", would point to "be",
                /// - "t|o be or ", would point to "to",
                /// - "to be or| ", would point to end.
                ///
                ///                 
                /// Preconditions: the segment_index should have a mapping and \a p should be valid iterator
                /// to the text in the mapped range.
                ///
                /// The returned iterator is invalidated by access to any non-const member functions of this object
                ///
                iterator find(base_iterator p) const
                {
                    return iterator(p,&map_,mask_,full_select_);
                }
               
                ///
                /// Get the mask of rules that are used
                /// 
                rule_type rule() const
                {
                    return mask_;
                }
                ///
                /// Set the mask of rules that are used
                /// 
                void rule(rule_type v)
                {
                    mask_ = v;
                }

                ///
                /// Get the full_select property value -  should segment include in the range
                /// values that not belong to specific \ref rule() or not.
                ///
                /// The default value is false.
                ///
                /// For example for \ref sentence %boundary with rule \ref sentence_term the segments
                /// of text "Hello! How\nare you?" are "Hello!\", "are you?" when full_select() is false
                /// because "How\n" is selected %as sentence by a rule spits the text by line feed. If full_select()
                /// is true the returned segments are "Hello! ", "How\nare you?" where "How\n" is joined with the
                /// following part "are you?"
                ///

                bool full_select()  const 
                {
                    return full_select_;
                }

                ///
                /// Set the full_select property value -  should segment include in the range
                /// values that not belong to specific \ref rule() or not.
                ///
                /// The default value is false.
                ///
                /// For example for \ref sentence %boundary with rule \ref sentence_term the segments
                /// of text "Hello! How\nare you?" are "Hello!\", "are you?" when full_select() is false
                /// because "How\n" is selected %as sentence by a rule spits the text by line feed. If full_select()
                /// is true the returned segments are "Hello! ", "How\nare you?" where "How\n" is joined with the
                /// following part "are you?"
                ///

                void full_select(bool v) 
                {
                    full_select_ = v;
                }
                
            private:
                friend class boundary_point_index<base_iterator>;
                typedef details::mapping<base_iterator> mapping_type;
                mapping_type  map_;
                rule_type mask_;
                bool full_select_;
            };

            ///
            /// \brief This class holds an index of \ref boundary_point "boundary points" and allows iterating
            /// over them.
            ///
            /// This class is provides \ref begin() and \ref end() member functions that return bidirectional iterators
            /// to the \ref boundary_point objects.
            ///
            /// It provides an option that affects selecting %boundary points according to different rules:
            /// using \ref rule(rule_type mask) member function. It allows to set a mask that select only specific
            /// types of %boundary points like \ref sentence_term.
            ///
            /// For example for a sentence %boundary analysis of a text "Hello! How\nare you?" when the default
            /// rule is used the %boundary points would be:
            ///
            /// - "|Hello! How\nare you?"
            /// - "Hello! |How\nare you?"
            /// - "Hello! How\n|are you?"
            /// - "Hello! How\nare you?|"
            ///
            /// However if \ref rule() is set to \ref sentence_term then the selected %boundary points would be: 
            ///
            /// - "|Hello! How\nare you?"
            /// - "Hello! |How\nare you?"
            /// - "Hello! How\nare you?|"
            /// 
            /// Such that a %boundary point defined by a line feed character would be ignored.
            ///     
            /// This class allows to find a boundary_point according to the given iterator in range using \ref find() member
            /// function.
            ///
            /// \note
            /// -   Even an empty text range [x,x) considered to have a one %boundary point x.
            /// -   \a a and \a b points of the range [a,b) are always considered %boundary points
            ///     regardless the rules used.
            /// -   Changing any of the option \ref rule() or course re-indexing the text
            ///     invalidates existing iterators and they can't be used any more.
            /// -   boundary_point_index can be created from segment_index or other boundary_point_index that was created with
            ///     same \ref boundary_type.  This is very fast operation %as they shared same index
            ///     and it does not require its regeneration.
            ///
            /// \see
            ///
            /// - \ref segment_index
            /// - \ref boundary_point
            /// - \ref segment
            ///


            template<typename BaseIterator>
            class boundary_point_index {
            public:
                ///
                /// The type of the iterator used to iterate over the original text
                ///
                typedef BaseIterator base_iterator;
                #ifdef BOOST_LOCALE_DOXYGEN
                ///
                /// The bidirectional iterator that iterates over \ref value_type objects.
                ///
                /// -   The iterators may be invalidated by use of any non-const member function
                ///     including but not limited to \ref rule(rule_type) member function.
                /// -   The returned value_type object is valid %as long %as iterator points to it.
                ///     So this following code is wrong %as t used after p was updated:
                ///     \code
                ///     boundary_point_index<some_iterator>::iterator p=index.begin();
                ///     boundary_point<some_iterator> &t = *p;
                ///     ++p;
                ///     rule_type r = t->rule();
                ///     \endcode
                ///
                typedef unspecified_iterator_type iterator;
                ///
                /// \copydoc iterator
                ///
                typedef unspecified_iterator_type const_iterator;
                #else
                typedef details::boundary_point_index_iterator<base_iterator> iterator;
                typedef details::boundary_point_index_iterator<base_iterator> const_iterator;
                #endif
                ///
                /// The type dereferenced by the \ref iterator and \ref const_iterator. It is
                /// an object that represents the selected \ref boundary_point "boundary point".
                ///
                typedef boundary_point<base_iterator> value_type;
                
                ///
                /// Default constructor. 
                ///
                /// \note
                ///
                /// When this object is constructed by default it does not include a valid index, thus
                /// calling \ref begin(), \ref end() or \ref find() member functions would lead to undefined
                /// behavior
                ///
                boundary_point_index() : mask_(0xFFFFFFFFu)
                {
                }
                
                ///
                /// Create a segment_index for %boundary analysis \ref boundary_type "type" of the text
                /// in range [begin,end) using a rule \a mask for locale \a loc.
                ///
                boundary_point_index(boundary_type type,
                            base_iterator begin,
                            base_iterator end,
                            rule_type mask,
                            std::locale const &loc=std::locale()) 
                    :
                        map_(type,begin,end,loc),
                        mask_(mask)
                {
                }
                ///
                /// Create a segment_index for %boundary analysis \ref boundary_type "type" of the text
                /// in range [begin,end) selecting all possible %boundary points (full mask) for locale \a loc.
                ///
                boundary_point_index(boundary_type type,
                            base_iterator begin,
                            base_iterator end,
                            std::locale const &loc=std::locale()) 
                    :
                        map_(type,begin,end,loc),
                        mask_(0xFFFFFFFFu)
                {
                }

                ///
                /// Create a boundary_point_index from a \ref segment_index. It copies all indexing information
                /// and uses the default rule (all possible %boundary points)
                ///
                /// This operation is very cheap, so if you use boundary_point_index and segment_index on same text
                /// range it is much better to create one from another rather then indexing the same
                /// range twice.
                ///
                /// \note \ref rule() flags are not copied
                ///
                boundary_point_index(segment_index<base_iterator> const &other);
                ///
                /// Copy a boundary_point_index from a \ref segment_index. It copies all indexing information
                /// and keeps the current \ref rule() unchanged
                ///
                /// This operation is very cheap, so if you use boundary_point_index and segment_index on same text
                /// range it is much better to create one from another rather then indexing the same
                /// range twice.
                ///
                /// \note \ref rule() flags are not copied
                ///
                boundary_point_index const &operator=(segment_index<base_iterator> const &other);

                ///
                /// Create a new index for %boundary analysis \ref boundary_type "type" of the text
                /// in range [begin,end) for locale \a loc.
                ///
                /// \note \ref rule() remains unchanged.
                ///
                void map(boundary_type type,base_iterator begin,base_iterator end,std::locale const &loc=std::locale())
                {
                    map_ = mapping_type(type,begin,end,loc);
                }

                ///
                /// Get the \ref iterator on the beginning of the %boundary points range.
                ///
                /// Preconditions: this boundary_point_index should have a mapping
                ///
                /// \note
                ///
                /// The returned iterator is invalidated by access to any non-const member functions of this object
                ///
                iterator begin() const
                {
                    return iterator(true,&map_,mask_);
                }

                ///
                /// Get the \ref iterator on the ending of the %boundary points range.
                ///
                /// Preconditions: this boundary_point_index should have a mapping
                ///
                /// \note
                ///
                /// The returned iterator is invalidated by access to any non-const member functions of this object
                ///
                iterator end() const
                {
                    return iterator(false,&map_,mask_);
                }

                ///
                /// Find a first valid %boundary point on a position \a p or following it.
                ///
                /// For example: For \ref word %boundary analysis of the text "to be or"
                ///
                /// - "|to be", would return %boundary point at "|to be",
                /// - "t|o be", would point to "to| be"
                ///                 
                /// Preconditions: the boundary_point_index should have a mapping and \a p should be valid iterator
                /// to the text in the mapped range.
                ///
                /// The returned iterator is invalidated by access to any non-const member functions of this object
                ///
                iterator find(base_iterator p) const
                {
                    return iterator(p,&map_,mask_);
                }
                
                ///
                /// Get the mask of rules that are used
                /// 
                rule_type rule() const
                {
                    return mask_;
                }
                ///
                /// Set the mask of rules that are used
                /// 
                void rule(rule_type v)
                {
                    mask_ = v;
                }

            private:

                friend class segment_index<base_iterator>;
                typedef details::mapping<base_iterator> mapping_type;
                mapping_type  map_;
                rule_type mask_;
            };
           
            /// \cond INTERNAL  
            template<typename BaseIterator>
            segment_index<BaseIterator>::segment_index(boundary_point_index<BaseIterator> const &other) :
                map_(other.map_),
                mask_(0xFFFFFFFFu),
                full_select_(false)
            {
            }
            
            template<typename BaseIterator>
            boundary_point_index<BaseIterator>::boundary_point_index(segment_index<BaseIterator> const &other) :
                map_(other.map_),
                mask_(0xFFFFFFFFu)
            {
            }

            template<typename BaseIterator>
            segment_index<BaseIterator> const &segment_index<BaseIterator>::operator=(boundary_point_index<BaseIterator> const &other)
            {
                map_ = other.map_;
                return *this;
            }
            
            template<typename BaseIterator>
            boundary_point_index<BaseIterator> const &boundary_point_index<BaseIterator>::operator=(segment_index<BaseIterator> const &other)
            {
                map_ = other.map_;
                return *this;
            }
            /// \endcond
          
            typedef segment_index<std::string::const_iterator> ssegment_index;      ///< convenience typedef
            typedef segment_index<std::wstring::const_iterator> wssegment_index;    ///< convenience typedef
            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            typedef segment_index<std::u16string::const_iterator> u16ssegment_index;///< convenience typedef
            #endif
            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            typedef segment_index<std::u32string::const_iterator> u32ssegment_index;///< convenience typedef
            #endif
           
            typedef segment_index<char const *> csegment_index;                     ///< convenience typedef
            typedef segment_index<wchar_t const *> wcsegment_index;                 ///< convenience typedef
            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            typedef segment_index<char16_t const *> u16csegment_index;              ///< convenience typedef
            #endif
            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            typedef segment_index<char32_t const *> u32csegment_index;              ///< convenience typedef
            #endif

            typedef boundary_point_index<std::string::const_iterator> sboundary_point_index;///< convenience typedef
            typedef boundary_point_index<std::wstring::const_iterator> wsboundary_point_index;///< convenience typedef
            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            typedef boundary_point_index<std::u16string::const_iterator> u16sboundary_point_index;///< convenience typedef
            #endif
            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            typedef boundary_point_index<std::u32string::const_iterator> u32sboundary_point_index;///< convenience typedef
            #endif
           
            typedef boundary_point_index<char const *> cboundary_point_index;       ///< convenience typedef
            typedef boundary_point_index<wchar_t const *> wcboundary_point_index;   ///< convenience typedef
            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            typedef boundary_point_index<char16_t const *> u16cboundary_point_index;///< convenience typedef
            #endif
            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            typedef boundary_point_index<char32_t const *> u32cboundary_point_index;///< convenience typedef
            #endif



        } // boundary

    } // locale
} // boost

///
/// \example boundary.cpp
/// Example of using segment_index
/// \example wboundary.cpp
/// Example of using segment_index over wide strings
///

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* index.hpp
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
*/