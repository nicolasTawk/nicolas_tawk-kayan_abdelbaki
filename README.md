# Advanced Data Structures Project

## Project Overview:

The project involves creating a C++ application to manage social networks made of the digraph data structure. Graphs consist of vertices and edges (connections between vertices). The application allows users to perform operations such as adding and removing vertices, connecting vertices with edges, finding the shortest path between vertices, traversing the graph using DFS or BFS, and other graph-related tasks. The goal is to implement these functionalities in an efficient and scalable manner using object-oriented programming principles.
Design Decisions and Considerations:
1.	**Graph Representation:** The graph is represented using an adjacency list data structure. Each vertex is stored as an object containing an ID and a list of adjacent vertices. This design choice was made due to its space efficiency, especially for sparse graphs, and its ability to facilitate fast traversal of adjacent vertices. The directed graph was chosen over the undirected one for one simple reason: our implementation considered a social network where a user can connect to another from one side only. In other words, our application is a replica of apps like Instagram, where you can follow and/or be followed, unlike other apps like Facebook, which are connected through friendships only. However, This implementation did indeed make our work more challenging.
2.	**Vertex and Edge Representation:** Vertices are represented as structures containing an ID and a linked list containing adjacent vertices. Edges are implicitly represented within the adjacency lists of vertices. This design simplifies the management of vertices and their connections.
3.	**User representation:** Users are represented as objects containing a unique identifier, which is the username, and other information related to the user, like their full name, email, and phone number. The user class is completely independent from the other classes to avoid circular dependencies and simplify modifications.
4.	**Main Representation:** The main class is the common ground between the User and Graph classes.  Although both User and Graph are independent, they are merged together in the Main class.
5.	**Standard Library Usage:** The project utilizes Standard Library containers (vectors and lists) and algorithms (iterators) extensively. These utilities simplify data management tasks and enhance code readability by providing efficient and standardized data structures and algorithms.

## Justification for Choosing This Data Structure Over Others:

When we have to decide which data structure, we need to use for this algorithm’s efficiency to be maximized, we need to take into consideration various factors like the time complexity and space complexity of the operations.
To solve such a problem, three data structures are suitable for algorithms that use graphs: adjacency lists, adjacency matrix, and edge lists. But to know which one is the most efficient, we need to look deeper into our problem and see which data structure will best fit our requirements.

2. **Space Efficiency:** Adjacency lists require less memory, especially for graphs, as they only store information about connected vertices, unlike the adjacency matrix, which stores information about all the possible connections. For example, if we had 5 vertices and 4 connections, the adjacency list would store 5 + 4 = 9 worth of memory units. However, the adjacency matrix will store 5^2, or 25 memory units.
2.	**Dynamic Nature:** Adjacency lists allow for efficient insertion and deletion of edges, making them suitable for dynamic graphs where vertices and edges are frequently added or removed (which is our case here; frequent insertion and deletion is essential for our problem).
3.	**Traversal Efficiency:** Adjacency lists facilitate the efficient traversal of adjacent vertices. Traversal algorithms, such as Breadth-First Search (BFS) and Depth-First Search (DFS), can be implemented more efficiently using adjacency lists compared to adjacency matrices or edge lists.
 
**Conclusion:**
Since our main goal is to implement an algorithm that would find the shortest path given a graph, and since this algorithm will use the BFS, and due to the factors listed above, choosing the adjacency list as our data structure is the best decision for this kind of problem.
 
## Implementation Details:

1.	**Vertex Structure:** Implements the properties of a vertex, including the id and the adjacency list that contains the edges.
2.	**Edge Structure:** contains the destination id, which is the id of a vertex to which another vertex is connected. Although this structure could have simply been implemented inside the vertex structure as a data field, We felt the need to use the edge keyword to greatly represent the components of the graph.
3.	**Graph Class:** Contains a vector that handles the vertices of our network. This class manages the collection of vertices and provides operations for adding, removing, and traversing vertices and edges.
4.	**Input/Output Handling:** Functions for reading graph data from files and displaying graph information to the user.
5.	**Algorithm Implementations:** Includes algorithms for traversing the graph (Breadth-First Search, Depth-First Search) and finding the shortest path between two vertices. And other algorithms to get the incoming or outgoing connections to or from a vertex, etc.

## Testing and validation:

The project underwent testing using integration tests. Test cases covered various scenarios, including:

2. **Adding and removing vertices and edges:** The testing covered the cases of adding a connection where the source and destination are identical, adding a connection that already exists, trying to remove a vertex/connection that does not exist, and many other specific cases were gracefully handled.
2.	**Finding paths between vertices**
3.	**Handling edge cases such as empty graphs and invalid inputs**

Testing helped ensure the correctness and robustness of the implemented functionalities.

## Challenges Faced:

1.	**Graph Traversal Algorithms:** Implementing algorithms like Breadth-First Search (BFS) and Depth-First Search (DFS) required careful consideration of data structures and recursion to ensure correctness and efficiency.
2.	**Input Validation:** Handling input data validation to prevent invalid graph configurations or erroneous operations posed a challenge, requiring thorough error checking and exception handling.
3.	**Choosing the best data structure:** choosing the data structure was one of the most difficult tasks we faced while doing this project due to the various functions we wanted to implement, some of which would have been more efficient with another data structure, but finding the shortest path was our main goal. We decided to use the adjacency list.
4.	**Ensuring a somewhat decent user interface:** The visuals were also a hard part, especially because we wanted our project to be acceptable in terms of views.

## Lessons Learned:

1.	**Algorithm Optimization:** Learned techniques for optimizing graph traversal algorithms to improve performance, such as using visited flags to avoid redundant exploration of vertices.
2.	**Handling Special Cases:** Learned to handle special cases, for example, when inserting or removing vertices and gracefully handling bas user inputs.
3.	**Assuring Independence:** I learned the importance of keeping the classes independent of each other and making them work on their own, which is crucial for testing and debugging.
4.	**Using graphs and an adjacency list:**
5.	**Error Handling:** Gained experience in implementing robust error handling mechanisms to gracefully handle unexpected inputs or runtime errors.

## Future Enhancements:

1.	**Graph Visualization:** Implement a graphical user interface (GUI) for visualizing graphs and their properties, making it easier for users to interact with the graph. This might also help students to understand the data structure and to visualize algorithms like DFS and BFS.
2.	**Additional Algorithms:** Expand the range of supported graph algorithms, such as minimum spanning tree algorithms and shortest path algorithms with weighted edges, to increase the utility of the application.
3.  **Performance Optimization:** Further optimize data structures and algorithms to enhance scalability and efficiency for larger graphs, enabling the application to handle more complex scenarios with improved performance.
 
