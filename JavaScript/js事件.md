# 事件分级
DOM 0 ,DOM 2,DOM 3 

```javascript
//DOM0
element.onclick = function (){}
//DOM2
element.addEventListener("click",function(){},false)
//DOM3
element.addEventListener("keyup",function(){},false)
```
其中里面最后个参数是代表捕获(true)和冒泡(false)，默认是false冒泡

# DOM事件类型:冒泡和捕获
冒泡是从
window→document→html→body→div→text
捕获是从
window←document←html←body←div←text
其中html是利用document.documentElement获得


# DOM事件api
```javascript
event.preventDefault() //阻止默认事件
event.stopPropagation()  //阻止冒泡
event.stopImmediatePropagation() //官方解释。阻止调用相同事件的其他侦听器。
event.currentTarget() 
event.target  
``` 
# event.preventDefault()
**阻止默认事件**
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>event.preventDefault()</title>
</head>
<body>
    <p>请点击复选框控件</p>
    <form>
        <label for="id-checkbox">Checkbox</label>
        <input type="checkbox" id="id-checkbox" name="checkbox" />
    </form>
    <script>
        document.querySelector("#id-checkbox").addEventListener("click", function(event){
            event.preventDefault();  //阻止该复选框被勾选
            setTimeout(function (){
              alert("preventDefault会阻止该复选框被勾选.")
            },0)
        }, false);
    </script>
</body>
</html>
```
当你选择时候会触发此事件(alert)，并且不会被选中

# stopImmediatePropagation()
某个元素有多个相同类型事件的事件监听函数,则当该类型的事件触发时,多个事件监听函数将按照顺序**依次执行**.如果某个监听函数执行了 event.stopImmediatePropagation()方法,则除了该事件的冒泡行为被阻止之外(event.stopPropagation方法的作用),该元素绑定的后序相同类型事件的监听函数的执行也将被阻止.
```javascript
<!DOCTYPE html>
<html>
    <head>
        <style>
            p { height: 30px; width: 150px; background-color: #ccf; }
            div {height: 30px; width: 150px; background-color: #cfc; }
        </style>
    </head>
    <body>
        <div>
            <p>paragraph</p>
        </div>
        <script>
            document.querySelector("p").addEventListener("click", function(event)
            {
                alert("我是p元素上被绑定的第一个监听函数");
            }, false);
            document.querySelector("p").addEventListener("click", function(event)
            {
                alert("我是p元素上被绑定的第二个监听函数");
                event.stopImmediatePropagation();
                //执行stopImmediatePropagation方法,阻止click事件冒泡,并且
                //阻止p元素上绑定的其他click事件的事件监听函数的执行.
            }, false);
            document.querySelector("p").addEventListener("click", function(event)
            {
                alert("我是p元素上被绑定的第三个监听函数");
                //该监听函数排在上个函数后面,该函数不会被执行.
            }, false);
            document.querySelector("div").addEventListener("click", function(event)
            {
                alert("我是div元素,我是p元素的上层元素");
                //p元素的click事件没有向上冒泡,该函数不会被执行.
            }, false);
        </script>
    </body>
</html>
```

# event.currentTarget() 
如下代码所示，

```html
   <ul id="f">
                <li class="item1">1</li>
                <li class="item2">2</li>
     </ul>
　　<script type="text/javascript">
        document.getElementById("f").onclick = function  (event) {
            console.log(event.target);//<li class="item2">
            console.log(event.currentTarget);//<ul id="f">
        }
    </script>
```


# event.target
事件属性可返回事件的目标节点
```html

<html>
 <body>
  <ul id="ul">
  <span>1</span>
  <p>2</p>
  <li>3</li>
  </ul>
  <script>
    var ul = document.getElementById("ul");
             ul.onclick = function(event){
             var tar = event.target;
             var tagName = tar.nodeName.toLowerCase();
             alert("你点击了:"+tagName);
             event.preventDefault();
 }

 </script>

</body>
</html>
```
下面的demo是创建一个元素并点击删除删除这个元素的例子。

```html
<head>
</head>
<input type="text" id="text">
<input type="button" value="添加" id="button">
<ul>
  <li>第1个
    <button class="btn" id="1">删除</button>
  </li>
  <li>第2个
    <button class="btn" id="2">删除</button>
  </li>
  <li>第3个
    <button class="btn" id="3">删除</button>
  </li>
</ul>

<body>
  <script>
    var button = document.getElementById("button");
    var text = document.getElementById("text");
    var ul = document.getElementsByTagName("ul")[0];
    var btnClass = document.getElementsByClassName("btn");
    button.onclick = function () {
      var deleteButton = document.createElement("button");
      var value = text.value;
      deleteButton.setAttribute("class", "btn");
      var deleteText = document.createTextNode("删除");
      deleteButton.appendChild(deleteText);
      var li = document.createElement("li");
      var liText = document.createTextNode(value);
      //在此处添加一个组件，包含text和button，后面会将button绑定删除事件
      li.appendChild(liText);
      li.appendChild(deleteButton);
      ul.appendChild(li);
      for (var i = 0; i < btnClass.length; i++) {
        btnClass[i].onclick = function () {
          console.log(this, this.parentNode, this.parentNode.parentNode);
          this.parentNode.parentNode.removeChild(this.parentNode);
        }
      }
    }
    for (var i = 0; i < btnClass.length; i++) {
      btnClass[i].onclick = function () {
      //绑定事件后进行删除
        this.parentNode.parentNode.removeChild(this.parentNode);
      }
    }
  </script>
</body>

</html>
```
