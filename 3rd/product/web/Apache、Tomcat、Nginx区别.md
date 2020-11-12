* Apache/Nginx 应该叫做「HTTP Server」；它关心的是 HTTP 协议层面的传输和访问控制(如代理、负载均衡等功能)
    * 其本身不支持动态页面
* Tomcat 则是一个「Application Server」，或者更准确的来说，是一个「Servlet/JSP」应用的容器 ；
    * 首先它支持开发语言的 Runtime（对于Tomcat是Java），保证应用能够在应用服务器上正常运行。
    * 其次，需要支持应用相关的规范，例如类库、安全方面的特性（对于Tomcat，就是提供 JSP/Sevlet 运行需要的标准类库、Interface 等）。
    * 最后执行应用，将动态的内容转化为静态的内容之后，通过 HTTP Server 分发到客户端。
    * 为了方便，应用服务器(Tomcat)往往也会集成 HTTP Server 的功能，但是不如专业的 HTTP Server 那么强大   
* 一般应用服务器往往是运行在 HTTP Server 的背后，比如Tomcat和Nginx组合使用
    * 动静态资源分离，运用Nginx的反向代理功能分发请求：所有动态资源的请求交给Tomcat，而静态资源的请求（例如图片、视频、CSS、JavaScript文件等）则直接由Nginx返回到浏览器，这样能大大减轻Tomcat的压力。
    * 负载均衡，当业务压力增大时，可能一个Tomcat的实例不足以处理，那么这时可以启动多个Tomcat实例进行水平扩展，而Nginx的负载均衡功能可以把请求通过算法分发到各个不同的实例进行处理