# CS300-Analysis-and-Design
**What was the problem you were solving in the projects for this course?**

The core problem solved across these projects was efficiently managing, storing, searching, and sorting large datasets—specifically municipal auction bids and Computer Science program course catalogs. Traditional linear data structures fail to scale efficiently when processing thousands of records. The goal was to implement, test, and compare advanced data structures (such as hash tables and binary search trees) and sorting algorithms to optimize computational run-time and memory utilization.

**How did you approach the problem? Consider why data structures are important to understand.**

The approach involved analyzing the specific performance constraints of each problem and selecting the appropriate data structure or algorithm (such as alphanumeric sorting for course catalogs or binary search trees for fast lookups). Understanding data structures is crucial because choosing the right container directly dictates the efficiency, scalability, and resource consumption of an application. Knowing when to use a hash table for $O(1)$ retrieval versus a tree structure for ordered hierarchical data prevents performance bottlenecks in software engineering.

**How did you overcome any roadblocks you encountered while going through the activities or project?**

Roadblocks—such as memory leaks during node deletion, pointer mis-links in chained hash tables, or tree balancing edge cases—were overcome through systematic debugging, careful pointer tracking, and implementing recursive helper functions (such as clean destructor traversals). Testing code incrementally with smaller datasets (like the 76-record sample file) before running it against the larger 12,000+ record CSV files helped isolate errors quickly.

**How has your work on this project expanded your approach to designing software and developing programs?**

Working on these projects expanded software design thinking by emphasizing algorithmic complexity ($Big-O$ notation) and modular architecture. It highlighted that software development is not just about making code "work," but about designing systems that remain performant and scalable under heavy data loads.

**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**

This work refined programming practices by reinforcing the Single Responsibility Principle, modular class design, and thorough documentation. Maintaining original starter comments and attributions while cleanly implementing FIXME blocks ensured that code remains structured, readable to other developers, and easily adaptable for future extensions or integration into a professional portfolio.
