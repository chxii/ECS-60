        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include "vector.h"
        //#include "mystring.h"
        #include <cstring>
        #include <cstdlib>


        class AdjListNode
        {
        public:
            int dest;
            int capacity;
            int index;

            AdjListNode()
            {
                capacity = 0;
            }
            AdjListNode(int d, int c, int i): dest(d), capacity(c), index(i){}
        };

        class AdjList
        {
        public:
            AdjListNode *adj;
            int size;
            int src;
            int index;

            bool operator != (const AdjList &rhs) const
            {
                return this->src!=rhs.src;
            }

            AdjList() {}
            AdjList(int p1): size(0), src(p1), index(0) {}
            AdjList(int z, int s, int d): size(z), src(s), index(d) 
            {
                adj = new AdjListNode[500];      
            }

            int findSrc(int src)
            {
                for (int i = 0; i < size; i++)
                {
                    if (adj[i].dest == src)
                        return adj[i].capacity;
                }
                return -1;
            }

            void minusSrc(int src, int path_flow)
            {
                for (int i = 0; i < size; i++)
                {
                    if (adj[i].dest == src)
                        adj[i].capacity = adj[i].capacity - path_flow;

                }
            }

            void plusSrc(int src, int path_flow)
            {
                for (int i = 0; i < size; i++)
                {
                    if (adj[i].dest == src)
                         adj[i].capacity = adj[i].capacity + path_flow;
                }
            }

        };
        
        //template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable( const AdjList & notFound, int size = 101 );
            // QuadraticHashTable( const AdjList & rhs )
            //   : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
            //     array( rhs.array ), currentSize( rhs.currentSize ) { }

             AdjList & find( const AdjList & x ) ;

            void makeEmpty( );
            void insert( const AdjList & x );
            void remove( const AdjList & x );

            QuadraticHashTable & operator=( const QuadraticHashTable & rhs );

            enum EntryType { ACTIVE, EMPTY, DELETED };
          //private:
            struct HashEntry
            {
                AdjList element;
                EntryType info;

                HashEntry( const AdjList & e = AdjList( ), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };

            vector<HashEntry> array;
            int currentSize;
             AdjList ITEM_NOT_FOUND;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( const AdjList & x ) const;
            //int hash( string & key, int tableSize ) const;
            int hash( int key, int tableSize ) const;
            int hash( AdjList key, int tableSize ) const;
            void rehash( );
        };

        //#include "QuadraticProbing.cpp"
        #endif
