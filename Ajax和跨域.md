# Ajax和跨域

## 跨域发生原因

原因1.浏览器端口/协议/域名不一样  2.发送xhr对象     **跨域产生的原因是客户端的限制**

## **跨域存在的意义**

 

## 跨域解决思路:      

1.利用**jsonp** ，通过动态创建的script标签进行跨域访问。(服务器需要改动)

跨域**服务端修改**: 

2.通过**服务器发送字段**，让浏览器支持跨域

Access-Control-Allow-origin :true

3.**正向代理：** 我借助与我的服务器, 像数据服务器发送数据, 我的服务器只需要向数据服务器发送get请求即可

4.**反向代理：**和正向代理类似, 但是不借助于脚本, 而是直接使用 服务器映射 url.

eg： 我们的 url 是 http://studyit.com

数据服务器的 url 是 http://api.botue.com/login

在apache配置一个 url 的代理映射

理论上使用 url: http://studyit.com/api 是在网站根目录下找 api 文件夹

但是现在 apache 提供一个映射的功能, 将 /api 映射到 http://api.botue.com

有了这个映射, 那么 访问 http://api.botue.com/login 就可以利用 /api/login来访问了

5.**浏览器关闭检查**进行跨域

利用 --args --disable-web-security  --user-data-dir

**Apache HTTP Server**    

## JSONP跨域方式解析

| 解释  | Name                      | Status | Protocol | Type   | Content-Type           |
| :---- | ------------------------- | ------ | -------- | ------ | ---------------------- |
| 正常  | Get1                      | 200    | http/1.1 | xhr    | application/json       |
| jsonp | Get1?callback=JQuery412…. | 200    | http/1.1 | script | application/javascript |

根本区别是Type值不同，底层原理也不相同，callback是返回的是夹杂json的js代码片段。

如果改成callback2会发生获取的值是json，这也是后台和前端约定俗成的方式，如果后台是callback，返回改成callbak2，会发生获取值callback2=json的形式，

参数使用一次就会被销毁例如jquery源码中体现的

```javascript
	if ( s.crossDomain ) {
		var script, callback;
		return {
			send: function( _, complete ) {
				script = jQuery( "<script>" ).prop( {
					charset: s.scriptCharset,
					src: s.url
				} ).on(
					"load error",
					callback = function( evt ) {
						script.remove();
						callback = null;
						if ( evt ) {
							complete( evt.type === "error" ? 404 : 200, evt.type );
						}
					}
				);

				// Use native DOM manipulation to avoid our domManip AJAX trickery
				document.head.appendChild( script[ 0 ] );
			},
			abort: function() {
				if ( callback ) {
					callback();
				}
			}
		};
	}
```

callback会返回jQuery110206957915709923779_1519612937942_这个值，这个值后面会有下划线，但是如果加上**Cache**: 如果为true,表示结果可以被缓存，callback后面的请求参数下划线消失，

##### callback的意义

你到一个商店买东西，刚好你要的东西没有货，于是你在店员那里留下了你的电话，过了几天店里有货了，店员就打了你的电话，然后你接到电话后就到店里去取了货。在这个例子里，你的电话号码就叫回调函数，你把电话留给店员就叫登记回调函数，店里后来有货了叫做触发了回调关联的事件，店员给你打电话叫做调用回调函数，你到店里去取货叫做响应回调事件。(转自zh)

## JSONP弊端

1.服务器需要改动支持

2.只支持GET(强行请求post也会自动生成GET请求)

3.发送的不是XHR请求(废话)

## 跨域简单请求和非简单请求

#### 简单请求:

方法为GET,HEAD,POST

请求header里面

   无自定义头

Content-Type为一下几种:

​      text/plain

​      mulipart/from-data

​      application/x-www-form-urlenoded

#### 非简单请求/复杂请求:

​    put,delete方法的ajax请求

​    发送json格式的ajax请求

​    带自定义头的ajax请求

**复杂请求**表面上看起来和简单请求使用上差不多，但实际上浏览器发送了不止一个请求。其中最先发送的是一种"预请求"，此时作为服务端，也需要返回"预回应"作为响应。预请求实际上是对服务端的一种权限请求，只有当预请求成功返回，实际请求才开始执行。

预请求以**OPTIONS**形式发送，当中同样包含域，并且还包含了两项CORS特有的内容：

**OPTIONS**预检命令缓存

添加Access-Control-Max-Age头部命令 可以起到缓存作用

可以参考https://www.poorren.com/cross-origin-resource-sharing-simple-complex



#### 带Cookie的跨域

不可以用Access

## XHR的用法

ajax跨域的一个重要对象就是**XMLHttpRequest**对象，

使用 XHR 对象时，要调用的第一个方法是 open()。

（"get"、"post"等)、请求的 URL，是否异步发送请求

```javascript
     xhr.open("get", "example.php", false);
```

这行代码会启动一个针对 example.php 的 GET 请求。有关这行代码，需要说明两点:一是 URL 5相对于执行代码的当前页面(当然也可以使用绝对路径);二是调用 open()方法并不会真正发送请求，而只是启动一个请求以备发送。

然后调用 send()方法才能实现发送

```javascript
xhr.send(null);
```

响应之后数据会自动添加到XHR 对象的属性，

- **responseText**:作为响应主体被返回的文本。


- **responseXML**:如果响应的内容类型是"text/xml"或"application/xml"，这个属性中将保存包含着响应数据的 XML DOM 文档。


- **status**:响应的 HTTP 状态。


- **statusText**:HTTP 状态的说明 

代码如下

```javascript
var xhr = new XMLHttpRequest();
xhr.open("get", "example.txt", false);
xhr.send(null);
if ((xhr.status >= 200 && xhr.status < 300) || xhr.status == 304){
   alert(xhr.responseText);
} else {
    alert("Request was unsuccessful: " + xhr.status);
}
```

根据返回的**状态代码**，这个例子会显示由服务器返回的内容/错误消息。通过检测 status 来决定下一步的操作，不要依赖 statusText，因为后者在跨浏览器使 用时不太可靠。另外，无论内容类型是什么，响应主体的内容都会保存到 responseText 属性中;而 对于非 XML 数据而言，responseXML 属性的值将为 null。

