// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#warning \
    "Use of relaxed_heap is depreciated; please use the standard heap functions."
#ifndef BOOST_RELAXED_HEAP_HEADER
#define BOOST_RELAXED_HEAP_HEADER

#include <boost/config/header_deprecated.hpp>
BOOST_HEADER_DEPRECATED("the standard heap functions")

#include <functional>
#include <boost/property_map/property_map.hpp>
#include <boost/optional.hpp>
#include <vector>
#include <climits> // for CHAR_BIT
#include <boost/none.hpp>

#ifdef BOOST_RELAXED_HEAP_DEBUG
#include <iostream>
#endif // BOOST_RELAXED_HEAP_DEBUG

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable : 4355) // complaint about using 'this' to
#endif // initialize a member

namespace boost
{

template < typename IndexedType, typename Compare = std::less< IndexedType >,
    typename ID = identity_property_map >
class relaxed_heap
{
    struct group;

    typedef relaxed_heap self_type;
    typedef std::size_t rank_type;

public:
    typedef IndexedType value_type;
    typedef rank_type size_type;

private:
    /**
     * The kind of key that a group has. The actual values are discussed
     * in-depth in the documentation of the @c kind field of the @c group
     * structure. Note that the order of the enumerators *IS* important
     * and must not be changed.
     */
    enum group_key_kind
    {
        smallest_key,
        stored_key,
        largest_key
    };

    struct group
    {
        explicit group(group_key_kind kind = largest_key)
        : kind(kind), parent(this), rank(0)
        {
        }

        /** The value associated with this group. This value is only valid
         *  when @c kind!=largest_key (which indicates a deleted
         *  element). Note that the use of boost::optional increases the
         *  memory requirements slightly but does not result in extraneous
         *  memory allocations or deallocations. The optional could be
         *  eliminated when @c value_type is a model of
         *  DefaultConstructible.
         */
        ::boost::optional< value_type > value;

        /**
         * The kind of key stored at this group. This may be @c
         * smallest_key, which indicates that the key is infinitely small;
         * @c largest_key, which indicates that the key is infinitely
         * large; or @c stored_key, which means that the key is unknown,
         * but its relationship to other keys can be determined via the
         * comparison function object.
         */
        group_key_kind kind;

        /// The parent of this group. Will only be NULL for the dummy root group
        group* parent;

        /// The rank of this group. Equivalent to the number of children in
        /// the group.
        rank_type rank;

        /** The children of this group. For the dummy root group, these are
         * the roots. This is an array of length log n containing pointers
         * to the child groups.
         */
        group** children;
    };

    size_type log_base_2(size_type n) // log2 is a macro on some platforms
    {
        size_type leading_zeroes = 0;
        do
        {
            size_type next = n << 1;
            if (n == (next >> 1))
            {
                ++leading_zeroes;
                n = next;
            }
            else
            {
                break;
            }
        } while (true);
        return sizeof(size_type) * CHAR_BIT - leading_zeroes - 1;
    }

public:
    relaxed_heap(
        size_type n, const Compare& compare = Compare(), const ID& id = ID())
    : compare(compare), id(id), root(smallest_key), groups(n), smallest_value(0)
    {
        if (n == 0)
        {
            root.children = new group*[1];
            return;
        }

        log_n = log_base_2(n);
        if (log_n == 0)
            log_n = 1;
        size_type g = n / log_n;
        if (n % log_n > 0)
            ++g;
        size_type log_g = log_base_2(g);
        size_type r = log_g;

        // Reserve an appropriate amount of space for data structures, so
        // that we do not need to expand them.
        index_to_group.resize(g);
        A.resize(r + 1, 0);
        root.rank = r + 1;
        root.children = new group*[(log_g + 1) * (g + 1)];
        for (rank_type i = 0; i < r + 1; ++i)
            root.children[i] = 0;

        // Build initial heap
        size_type idx = 0;
        while (idx < g)
        {
            root.children[r] = &index_to_group[idx];
            idx = build_tree(root, idx, r, log_g + 1);
            if (idx != g)
                r = static_cast< size_type >(log_base_2(g - idx));
        }
    }

    ~relaxed_heap() { delete[] root.children; }

    void push(const value_type& x)
    {
        groups[get(id, x)] = x;
        update(x);
    }

    void update(const value_type& x)
    {
        group* a = &index_to_group[get(id, x) / log_n];
        if (!a->value || *a->value == x || compare(x, *a->value))
        {
            if (a != smallest_value)
                smallest_value = 0;
            a->kind = stored_key;
            a->value = x;
            promote(a);
        }
    }

    void remove(const value_type& x)
    {
        group* a = &index_to_group[get(id, x) / log_n];
        assert(groups[get(id, x)]);
        a->value = x;
        a->kind = smallest_key;
        promote(a);
        smallest_value = a;
        pop();
    }

    value_type& top()
    {
        find_smallest();
        assert(smallest_value->value != none);
        return *smallest_value->value;
    }

    const value_type& top() const
    {
        find_smallest();
        assert(smallest_value->value != none);
        return *smallest_value->value;
    }

    bool empty() const
    {
        find_smallest();
        return !smallest_value || (smallest_value->kind == largest_key);
    }

    bool contains(const value_type& x) const
    {
        return static_cast< bool >(groups[get(id, x)]);
    }

    void pop()
    {
        // Fill in smallest_value. This is the group x.
        find_smallest();
        group* x = smallest_value;
        smallest_value = 0;

        // Make x a leaf, giving it the smallest value within its group
        rank_type r = x->rank;
        group* p = x->parent;
        {
            assert(x->value != none);

            // Find x's group
            size_type start = get(id, *x->value) - get(id, *x->value) % log_n;
            size_type end = start + log_n;
            if (end > groups.size())
                end = groups.size();

            // Remove the smallest value from the group, and find the new
            // smallest value.
            groups[get(id, *x->value)].reset();
            x->value.reset();
            x->kind = largest_key;
            for (size_type i = start; i < end; ++i)
            {
                if (groups[i] && (!x->value || compare(*groups[i], *x->value)))
                {
                    x->kind = stored_key;
                    x->value = groups[i];
                }
            }
        }
        x->rank = 0;

        // Combine prior children of x with x
        group* y = x;
        for (size_type c = 0; c < r; ++c)
        {
            group* child = x->children[c];
            if (A[c] == child)
                A[c] = 0;
            y = combine(y, child);
        }

        // If we got back something other than x, let y take x's place
        if (y != x)
        {
            y->parent = p;
            p->children[r] = y;

            assert(r == y->rank);
            if (A[y->rank] == x)
                A[y->rank] = do_compare(y, p) ? y : 0;
        }
    }

#ifdef BOOST_RELAXED_HEAP_DEBUG
    /*************************************************************************
     * Debugging support                                                     *
     *************************************************************************/
    void dump_tree() { dump_tree(std::cout); }
    void dump_tree(std::ostream& out) { dump_tree(out, &root); }

    void dump_tree(std::ostream& out, group* p, bool in_progress = false)
    {
        if (!in_progress)
        {
            out << "digraph heap {\n"
                << "  edge[dir=\"back\"];\n";
        }

        size_type p_index = 0;
        if (p != &root)
            while (&index_to_group[p_index] != p)
                ++p_index;

        for (size_type i = 0; i < p->rank; ++i)
        {
            group* c = p->children[i];
            if (c)
            {
                size_type c_index = 0;
                if (c != &root)
                    while (&index_to_group[c_index] != c)
                        ++c_index;

                out << "  ";
                if (p == &root)
                    out << 'p';
                else
                    out << p_index;
                out << " -> ";
                if (c == &root)
                    out << 'p';
                else
                    out << c_index;
                if (A[c->rank] == c)
                    out << " [style=\"dotted\"]";
                out << ";\n";
                dump_tree(out, c, true);

                // Emit node information
                out << "  ";
                if (c == &root)
                    out << 'p';
                else
                    out << c_index;
                out << " [label=\"";
                if (c == &root)
                    out << 'p';
                else
                    out << c_index;
                out << ":";
                size_type start = c_index * log_n;
                size_type end = start + log_n;
                if (end > groups.size())
                    end = groups.size();
                while (start != end)
                {
                    if (groups[start])
                    {
                        out << " " << get(id, *groups[start]);
                        if (*groups[start] == *c->value)
                            out << "(*)";
                    }
                    ++start;
                }
                out << '"';

                if (do_compare(c, p))
                {
                    out << "  ";
                    if (c == &root)
                        out << 'p';
                    else
                        out << c_index;
                    out << ", style=\"filled\", fillcolor=\"gray\"";
                }
                out << "];\n";
            }
            else
            {
                assert(p->parent == p);
            }
        }
        if (!in_progress)
            out << "}\n";
    }

    bool valid()
    {
        // Check that the ranks in the A array match the ranks of the
        // groups stored there. Also, the active groups must be the last
        // child of their parent.
        for (size_type r = 0; r < A.size(); ++r)
        {
            if (A[r] && A[r]->rank != r)
                return false;

            if (A[r] && A[r]->parent->children[A[r]->parent->rank - 1] != A[r])
                return false;
        }

        // The root must have no value and a key of -Infinity
        if (root.kind != smallest_key)
            return false;

        return valid(&root);
    }

    bool valid(group* p)
    {
        for (size_type i = 0; i < p->rank; ++i)
        {
            group* c = p->children[i];
            if (c)
            {
                // Check link structure
                if (c->parent != p)
                    return false;
                if (c->rank != i)
                    return false;

                // A bad group must be active
                if (do_compare(c, p) && A[i] != c)
                    return false;

                // Check recursively
                if (!valid(c))
                    return false;
            }
            else
            {
                // Only the root may
                if (p != &root)
                    return false;
            }
        }
        return true;
    }

#endif // BOOST_RELAXED_HEAP_DEBUG

private:
    size_type build_tree(
        group& parent, size_type idx, size_type r, size_type max_rank)
    {
        group& this_group = index_to_group[idx];
        this_group.parent = &parent;
        ++idx;

        this_group.children = root.children + (idx * max_rank);
        this_group.rank = r;
        for (size_type i = 0; i < r; ++i)
        {
            this_group.children[i] = &index_to_group[idx];
            idx = build_tree(this_group, idx, i, max_rank);
        }
        return idx;
    }

    void find_smallest() const
    {
        group** roots = root.children;

        if (!smallest_value)
        {
            std::size_t i;
            for (i = 0; i < root.rank; ++i)
            {
                if (roots[i]
                    && (!smallest_value
                        || do_compare(roots[i], smallest_value)))
                {
                    smallest_value = roots[i];
                }
            }
            for (i = 0; i < A.size(); ++i)
            {
                if (A[i]
                    && (!smallest_value || do_compare(A[i], smallest_value)))
                    smallest_value = A[i];
            }
        }
    }

    bool do_compare(group* x, group* y) const
    {
        return (x->kind < y->kind
            || (x->kind == y->kind && x->kind == stored_key
                && compare(*x->value, *y->value)));
    }

    void promote(group* a)
    {
        assert(a != 0);
        rank_type r = a->rank;
        group* p = a->parent;
        assert(p != 0);
        if (do_compare(a, p))
        {
            // s is the rank + 1 sibling
            group* s = p->rank > r + 1 ? p->children[r + 1] : 0;

            // If a is the last child of p
            if (r == p->rank - 1)
            {
                if (!A[r])
                    A[r] = a;
                else if (A[r] != a)
                    pair_transform(a);
            }
            else
            {
                assert(s != 0);
                if (A[r + 1] == s)
                    active_sibling_transform(a, s);
                else
                    good_sibling_transform(a, s);
            }
        }
    }

    group* combine(group* a1, group* a2)
    {
        assert(a1->rank == a2->rank);
        if (do_compare(a2, a1))
            do_swap(a1, a2);
        a1->children[a1->rank++] = a2;
        a2->parent = a1;
        clean(a1);
        return a1;
    }

    void clean(group* q)
    {
        if (2 > q->rank)
            return;
        group* qp = q->children[q->rank - 1];
        rank_type s = q->rank - 2;
        group* x = q->children[s];
        group* xp = qp->children[s];
        assert(s == x->rank);

        // If x is active, swap x and xp
        if (A[s] == x)
        {
            q->children[s] = xp;
            xp->parent = q;
            qp->children[s] = x;
            x->parent = qp;
        }
    }

    void pair_transform(group* a)
    {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "- pair transform\n";
#endif
        rank_type r = a->rank;

        // p is a's parent
        group* p = a->parent;
        assert(p != 0);

        // g is p's parent (a's grandparent)
        group* g = p->parent;
        assert(g != 0);

        // a' <- A(r)
        assert(A[r] != 0);
        group* ap = A[r];
        assert(ap != 0);

        // A(r) <- nil
        A[r] = 0;

        // let a' have parent p'
        group* pp = ap->parent;
        assert(pp != 0);

        // let a' have grandparent g'
        group* gp = pp->parent;
        assert(gp != 0);

        // Remove a and a' from their parents
        assert(ap
            == pp->children[pp->rank - 1]); // Guaranteed because ap is active
        --pp->rank;

        // Guaranteed by caller
        assert(a == p->children[p->rank - 1]);
        --p->rank;

        // Note: a, ap, p, pp all have rank r
        if (do_compare(pp, p))
        {
            do_swap(a, ap);
            do_swap(p, pp);
            do_swap(g, gp);
        }

        // Assuming k(p) <= k(p')
        // make p' the rank r child of p
        assert(r == p->rank);
        p->children[p->rank++] = pp;
        pp->parent = p;

        // Combine a, ap into a rank r+1 group c
        group* c = combine(a, ap);

        // make c the rank r+1 child of g'
        assert(gp->rank > r + 1);
        gp->children[r + 1] = c;
        c->parent = gp;

#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "After pair transform...\n";
        dump_tree();
#endif

        if (A[r + 1] == pp)
            A[r + 1] = c;
        else
            promote(c);
    }

    void active_sibling_transform(group* a, group* s)
    {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "- active sibling transform\n";
#endif
        group* p = a->parent;
        group* g = p->parent;

        // remove a, s from their parents
        assert(s->parent == p);
        assert(p->children[p->rank - 1] == s);
        --p->rank;
        assert(p->children[p->rank - 1] == a);
        --p->rank;

        rank_type r = a->rank;
        A[r + 1] = 0;
        a = combine(p, a);
        group* c = combine(a, s);

        // make c the rank r+2 child of g
        assert(g->children[r + 2] == p);
        g->children[r + 2] = c;
        c->parent = g;
        if (A[r + 2] == p)
            A[r + 2] = c;
        else
            promote(c);
    }

    void good_sibling_transform(group* a, group* s)
    {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "- good sibling transform\n";
#endif
        rank_type r = a->rank;
        group* c = s->children[s->rank - 1];
        assert(c->rank == r);
        if (A[r] == c)
        {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
            std::cerr << "- good sibling pair transform\n";
#endif
            A[r] = 0;
            group* p = a->parent;

            // Remove c from its parent
            --s->rank;

            // Make s the rank r child of p
            s->parent = p;
            p->children[r] = s;

            // combine a, c and let the result by the rank r+1 child of p
            assert(p->rank > r + 1);
            group* x = combine(a, c);
            x->parent = p;
            p->children[r + 1] = x;

            if (A[r + 1] == s)
                A[r + 1] = x;
            else
                promote(x);

#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
            dump_tree(std::cerr);
#endif
            //      pair_transform(a);
        }
        else
        {
            // Clean operation
            group* p = a->parent;
            s->children[r] = a;
            a->parent = s;
            p->children[r] = c;
            c->parent = p;

            promote(a);
        }
    }

    static void do_swap(group*& x, group*& y)
    {
        group* tmp = x;
        x = y;
        y = tmp;
    }

    /// Function object that compares two values in the heap
    Compare compare;

    /// Mapping from values to indices in the range [0, n).
    ID id;

    /** The root group of the queue. This group is special because it will
     *  never store a value, but it acts as a parent to all of the
     *  roots. Thus, its list of children is the list of roots.
     */
    group root;

    /** Mapping from the group index of a value to the group associated
     *  with that value. If a value is not in the queue, then the "value"
     *  field will be empty.
     */
    std::vector< group > index_to_group;

    /** Flat data structure containing the values in each of the
     *  groups. It will be indexed via the id of the values. The groups
     *  are each log_n long, with the last group potentially being
     *  smaller.
     */
    std::vector< ::boost::optional< value_type > > groups;

    /** The list of active groups, indexed by rank. When A[r] is null,
     *  there is no active group of rank r. Otherwise, A[r] is the active
     *  group of rank r.
     */
    std::vector< group* > A;

    /** The group containing the smallest value in the queue, which must
     *  be either a root or an active group. If this group is null, then we
     *  will need to search for this group when it is needed.
     */
    mutable group* smallest_value;

    /// Cached value log_base_2(n)
    size_type log_n;
};

} // end namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_RELAXED_HEAP_HEADER

/* relaxed_heap.hpp
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
*/