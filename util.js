


/* 将Linux时间戳转换为指定的格式
*  标准格式是: yyyy/MM/dd hh:mm:ss  可以自行更换顺序连接符
*  注意并未做详细的防御判断
*/
function FormatTime(t,date){
    var date=new Date(date * 1000);
    var o = {   
        "M+" : date.getMonth()+1,                 //月份   
        "d+" : date.getDate(),                    //日   
        "h+" : date.getHours(),                   //小时   
        "m+" : date.getMinutes(),                 //分   
        "s+" : date.getSeconds(),                 //秒   
        "q+" : Math.floor((date.getMonth()+3)/3), //季度   
        "S"  : date.getMilliseconds()             //毫秒   
    };   
    if(/(y+)/.test(t)){
        t=t.replace(RegExp.$1,(date.getFullYear()+"").substr(4-RegExp.$1.length)); 
    };    
    for(var k in o){
        if(new RegExp("("+ k +")").test(t)){
            t=t.replace(RegExp.$1,(RegExp.$1.length==1)?(o[k]):(("00"+ o[k]).substr((""+o[k]).length))); 
        }; 
    }
    return t; 
};

//复制到粘贴板, 并提示粘贴内容; 1.5s秒后变透明消失, 需要引入Jquery库
function copyToClipboard(prefix, text)
{
	if(document.getElementById("layer"))
	{
		return;
	}

	var layer = function(text)
	{
		var layer=document.createElement("div");
		layer.id="layer";
		var style={
           "top": "50px",
           "left": "50%",
           "padding": "10px",
           "transform": "translate(-50%,0%)",
           position: "Fixed",
           width: "auto",
           border: "1px solid rgba(0, 0, 0, 0.2)",
           "box-shadow": "0px 3px 9px rgba(0, 0, 0, 0.5)",
           "z-index": "10001",
           "border-radius": "6px",
           "background-color": "#3498db",
           "line-height": "18px",
           "color":"white",
        }
        for(var i in style)
            layer.style[i]=style[i];

        document.body.appendChild(layer);
        layer.innerHTML = prefix + text;
        layer.style.textAlign="center";
        
        setTimeout(function(){
        	$(layer).fadeOut(1500, function(){document.body.removeChild(layer)})
        }, 300)
		
	}

	var	textArea = document.createElement('textArea');
    textArea.innerHTML = text;
    textArea.value = text;
    document.body.appendChild(textArea);

    textArea.select();
    if(document.execCommand("Copy"))
    {
    	document.body.removeChild(textArea);
    	layer(text)
    }
}