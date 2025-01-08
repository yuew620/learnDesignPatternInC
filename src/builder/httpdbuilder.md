```mermaid
classDiagram
    class ResponseDirector {
        -ResponseBuilder* builder
        +handle_request(request_rec* r)
        +buildOkResponse()
        +buildErrorResponse()
        +buildRedirectResponse()
    }

    class ResponseBuilder {
        <<interface>>
        +setStatus(int status)
        +setHeaders(apr_table_t* headers)
        +setBody(apr_bucket_brigade* body)
        +setContentType(const char* type)
        +setContentLength(apr_size_t length)
        +setKeptBody(int kept)
        +build() http_response
    }

    class StandardResponseBuilder {
        -http_response* response
        +StandardResponseBuilder(request_rec* r)
        +setStatus(int status)
        +setHeaders(apr_table_t* headers)
        +setBody(apr_bucket_brigade* body)
        +setContentType(const char* type)
        +setContentLength(apr_size_t length)
        +setKeptBody(int kept)
        +build() http_response
    }

    class http_response {
        +request_rec* r
        +int status
        +apr_table_t* headers
        +apr_bucket_brigade* body
        +const char* content_type
        +apr_size_t content_length
        +int kept_body
    }

    ResponseDirector --> ResponseBuilder
    ResponseBuilder <|-- StandardResponseBuilder
    StandardResponseBuilder --> http_response

、、、