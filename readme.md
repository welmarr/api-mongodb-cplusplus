
CMakeLists.txt: The CMake configuration file for building the project.

    include/: This directory contains header files for the REST API and data models used in the API.

        api/: This directory contains header files for the REST API implementation.
            error.hpp: Header file for the Error class, which manages errors that may occur during API requests.
            request_handler.hpp: Header file for the RequestHandler class, which handles incoming API requests.
            route.hpp: Header file for the Route class, which defines an individual API route.
            router.hpp: Header file for the Router class, which manages all the routes for the API.
            singleton_mongo_client.hpp: Header file for the SingletonMongoClient class, which uses the Singleton pattern to provide a single connection to the MongoDB database.

        models/: This directory contains header files for data models used in the API.
            document.hpp: Header file for the document class, which represents a document stored in the MongoDB database.

    src/: This directory contains source files for the REST API and data models used in the API.

        api/: This directory contains source files for the REST API implementation.
            error.cpp: Source file for the Error class.
            request_handler.cpp: Source file for the RequestHandler class.
            route.cpp: Source file for the Route class.
            router.cpp: Source file for the Router class.
            singleton_mongo_client.cpp: Source file for the SingletonMongoClient class.

        main.cpp: The main source file for the project.

        models/: This directory contains implementation files for data models used in the API.
            document.cpp: Implementation file for the document class.

    vcpkg.json: The configuration file for the vcpkg package manager, which lists the required dependencies for the project.