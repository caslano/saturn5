/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_MAX_COVER_HPP
#define BOOST_POLYGON_MAX_COVER_HPP
namespace boost { namespace polygon{

  template <typename Unit>
  struct MaxCover {
    typedef interval_data<Unit> Interval;
    typedef rectangle_data<Unit> Rectangle;

    class Node {
    private:
      std::vector<Node*> children_;
      std::set<Interval> tracedPaths_;
    public:
      Rectangle rect;
      Node() : children_(), tracedPaths_(), rect() {}
      Node(const Rectangle rectIn) : children_(), tracedPaths_(), rect(rectIn) {}
      typedef typename std::vector<Node*>::iterator iterator;
      inline iterator begin() { return children_.begin(); }
      inline iterator end() { return children_.end(); }
      inline void add(Node* child) { children_.push_back(child); }
      inline bool tracedPath(const Interval& ivl) const {
        return tracedPaths_.find(ivl) != tracedPaths_.end();
      }
      inline void addPath(const Interval& ivl) {
        tracedPaths_.insert(tracedPaths_.end(), ivl);
      }
    };

    typedef std::pair<std::pair<Unit, Interval>, Node* > EdgeAssociation;

    class lessEdgeAssociation {
    public:
      typedef const EdgeAssociation& first_argument_type;
      typedef const EdgeAssociation& second_argument_type;
      typedef bool result_type;
      inline lessEdgeAssociation() {}
      inline bool operator () (const EdgeAssociation& elem1, const EdgeAssociation& elem2) const {
        if(elem1.first.first < elem2.first.first) return true;
        if(elem1.first.first > elem2.first.first) return false;
        return elem1.first.second < elem2.first.second;
      }
    };

    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient) {
      Interval rectIvl = node->rect.get(orient);
      if(node->tracedPath(rectIvl)) {
        return;
      }
      node->addPath(rectIvl);
      if(node->begin() == node->end()) {
        //std::cout << "WRITE OUT 3: " << node->rect << std::endl;
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(node->rect));
        return;
      }
      bool writeOut = true;
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        getMaxCover(outputContainer, *itr, orient, node->rect); //get rectangles down path
        Interval nodeIvl = (*itr)->rect.get(orient);
        if(contains(nodeIvl, rectIvl, true)) writeOut = false;
      }
      if(writeOut) {
        //std::cout << "WRITE OUT 2: " << node->rect << std::endl;
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(node->rect));
      }
    }

    struct stack_element {
      inline stack_element() :
        node(), rect(), itr() {}
      inline stack_element(Node* n,
                           const Rectangle& r,
                           typename Node::iterator i) :
        node(n), rect(r), itr(i) {}
      Node* node;
      Rectangle rect;
      typename Node::iterator itr;
    };

    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient,
                                   Rectangle rect) {
      //std::cout << "New Root\n";
      std::vector<stack_element> stack;
      typename Node::iterator itr = node->begin();
      do {
        //std::cout << "LOOP\n";
        //std::cout << node->rect << std::endl;
        Interval rectIvl = rect.get(orient);
        Interval nodeIvl = node->rect.get(orient);
        bool iresult = intersect(rectIvl, nodeIvl, false);
        bool tresult = !node->tracedPath(rectIvl);
        //std::cout << (itr != node->end()) << " " << iresult << " " << tresult << std::endl;
        Rectangle nextRect1 = Rectangle(rectIvl, rectIvl);
        Unit low = rect.get(orient.get_perpendicular()).low();
        Unit high = node->rect.get(orient.get_perpendicular()).high();
        nextRect1.set(orient.get_perpendicular(), Interval(low, high));
        if(iresult && tresult) {
          node->addPath(rectIvl);
          bool writeOut = true;
          //check further visibility beyond this node
          for(typename Node::iterator itr2 = node->begin(); itr2 != node->end(); ++itr2) {
            Interval nodeIvl3 = (*itr2)->rect.get(orient);
            //if a child of this node can contain the interval then we can extend through
            if(contains(nodeIvl3, rectIvl, true)) writeOut = false;
            //std::cout << "child " << (*itr2)->rect << std::endl;
          }
          Rectangle nextRect2 = Rectangle(rectIvl, rectIvl);
          Unit low2 = rect.get(orient.get_perpendicular()).low();
          Unit high2 = node->rect.get(orient.get_perpendicular()).high();
          nextRect2.set(orient.get_perpendicular(), Interval(low2, high2));
          if(writeOut) {
            //std::cout << "write out " << nextRect << std::endl;
            outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect2));
          } else {
            //std::cout << "suppress " << nextRect << std::endl;
          }
        }
        if(itr != node->end() && iresult && tresult) {
          //std::cout << "recurse into child\n";
          stack.push_back(stack_element(node, rect, itr));
          rect = nextRect1;
          node = *itr;
          itr = node->begin();
        } else {
          if(!stack.empty()) {
            //std::cout << "recurse out of child\n";
            node = stack.back().node;
            rect = stack.back().rect;
            itr = stack.back().itr;
            stack.pop_back();
          } else {
            //std::cout << "empty stack\n";
            //if there were no children of the root node
//             Rectangle nextRect = Rectangle(rectIvl, rectIvl);
//             Unit low = rect.get(orient.get_perpendicular()).low();
//             Unit high = node->rect.get(orient.get_perpendicular()).high();
//             nextRect.set(orient.get_perpendicular(), Interval(low, high));
//             outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect));
          }
          //std::cout << "increment " << (itr != node->end()) << std::endl;
          if(itr != node->end()) {
            ++itr;
            if(itr != node->end()) {
              //std::cout << "recurse into next child.\n";
              stack.push_back(stack_element(node, rect, itr));
              Interval rectIvl2 = rect.get(orient);
              Interval nodeIvl2 = node->rect.get(orient);
              /*bool iresult =*/ intersect(rectIvl2, nodeIvl2, false);
              Rectangle nextRect2 = Rectangle(rectIvl2, rectIvl2);
              Unit low2 = rect.get(orient.get_perpendicular()).low();
              Unit high2 = node->rect.get(orient.get_perpendicular()).high();
              nextRect2.set(orient.get_perpendicular(), Interval(low2, high2));
              rect = nextRect2;
              //std::cout << "rect for next child" << rect << std::endl;
              node = *itr;
              itr = node->begin();
            }
          }
        }
      } while(!stack.empty() || itr != node->end());
    }

    /*  Function recursive version of getMaxCover
        Because the code is so much simpler than the loop algorithm I retain it for clarity

    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient,
                                   const Rectangle& rect) {
      Interval rectIvl = rect.get(orient);
      Interval nodeIvl = node->rect.get(orient);
      if(!intersect(rectIvl, nodeIvl, false)) {
        return;
      }
      if(node->tracedPath(rectIvl)) {
        return;
      }
      node->addPath(rectIvl);
      Rectangle nextRect(rectIvl, rectIvl);
      Unit low = rect.get(orient.get_perpendicular()).low();
      Unit high = node->rect.get(orient.get_perpendicular()).high();
      nextRect.set(orient.get_perpendicular(), Interval(low, high));
      bool writeOut = true;
      rectIvl = nextRect.get(orient);
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        nodeIvl = (*itr)->rect.get(orient);
        if(contains(nodeIvl, rectIvl, true)) writeOut = false;
      }
      if(writeOut) {
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect));
      }
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        getMaxCover(outputContainer, *itr, orient, nextRect);
      }
    }
    */

    //iterator range is assummed to be in topological order meaning all node's trailing
    //edges are in sorted order
    template <class iT>
    static inline void computeDag(iT beginNode, iT endNode, orientation_2d orient,
                                  std::size_t size) {
      std::vector<EdgeAssociation> leadingEdges;
      leadingEdges.reserve(size);
      for(iT iter = beginNode; iter != endNode; ++iter) {
        Node* nodep = &(*iter);
        Unit leading = nodep->rect.get(orient.get_perpendicular()).low();
        Interval rectIvl = nodep->rect.get(orient);
        leadingEdges.push_back(EdgeAssociation(std::pair<Unit, Interval>(leading, rectIvl), nodep));
      }
      polygon_sort(leadingEdges.begin(), leadingEdges.end(), lessEdgeAssociation());
      typename std::vector<EdgeAssociation>::iterator leadingBegin = leadingEdges.begin();
      iT trailingBegin = beginNode;
      while(leadingBegin != leadingEdges.end()) {
        EdgeAssociation& leadingSegment = (*leadingBegin);
        Unit trailing = (*trailingBegin).rect.get(orient.get_perpendicular()).high();
        Interval ivl = (*trailingBegin).rect.get(orient);
        std::pair<Unit, Interval> trailingSegment(trailing, ivl);
        if(leadingSegment.first.first < trailingSegment.first) {
          ++leadingBegin;
          continue;
        }
        if(leadingSegment.first.first > trailingSegment.first) {
          ++trailingBegin;
          continue;
        }
        if(leadingSegment.first.second.high() <= trailingSegment.second.low()) {
          ++leadingBegin;
          continue;
        }
        if(trailingSegment.second.high() <= leadingSegment.first.second.low()) {
          ++trailingBegin;
          continue;
        }
        //leading segment intersects trailing segment
        (*trailingBegin).add((*leadingBegin).second);
        if(leadingSegment.first.second.high() > trailingSegment.second.high()) {
          ++trailingBegin;
          continue;
        }
        if(trailingSegment.second.high() > leadingSegment.first.second.high()) {
          ++leadingBegin;
          continue;
        }
        ++leadingBegin;
        ++trailingBegin;
      }
    }

    template <class cT>
    static inline void getMaxCover(cT& outputContainer,
                                   const std::vector<Rectangle>& rects, orientation_2d orient) {
      if(rects.empty()) return;
      std::vector<Node> nodes;
      {
        if(rects.size() == 1) {
          outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(rects[0]));
          return;
        }
        nodes.reserve(rects.size());
        for(std::size_t i = 0; i < rects.size(); ++i) { nodes.push_back(Node(rects[i])); }
      }
      computeDag(nodes.begin(), nodes.end(), orient, nodes.size());
      for(std::size_t i = 0; i < nodes.size(); ++i) {
        getMaxCover(outputContainer, &(nodes[i]), orient);
      }
    }

  };
}
}

#endif

/* max_cover.hpp
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
*/