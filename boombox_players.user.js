// ==UserScript==
// @name        CoderWizards(with team color)
// @namespace   qapjs
// @description coloring nicknames in the team color
// @version     v1 (2016.12.03)
// @grant       none
// @include     http://russianaicup.ru/profile/*
// @include     http://russianaicup.ru/games/creator/*
// @include     http://russianaicup.ru/games/with/*
// @include     http://russianaicup.ru/contest*
// @autor       Adler
// ==/UserScript==

  make_global([get_boombox_players_counter]);
  var g_counter=0;
  function get_boombox_players_counter(){return g_counter;}

  var loc=location.href;
  if(loc.includes("standings"))return;

  var arr2str=out=>"[\n"+out.map(e=>JSON.stringify(e)).join(",\n")+"\n]";
  var repelem=(elem,t,to)=>tag(elem,t).map(e=>e.outerHTML=to);
  function tag(e,s){return Array.from(e.getElementsByTagName(s));}
  q=document;
  var trs=q.getElementsByClassName("gamesTable")[0].getElementsByTagName("tbody")[0].getElementsByTagName("tr");
  function f(e,tr_id){
    //if(tr_id!=0)return;
    var names=tag(e,"span").filter(u=>u.className!="day").map(u=>u.innerHTML);
    var v=[];var points=[];var d=[];var id=-1;var token=0;
    tag(e,"td").forEach((td,i)=>{
      if(0==i)id=tag(td,"a").map(e=>e.innerHTML|0)[0];
      var ug5=td=>{tag(td,"hr").map(hr=>hr.outerHTML="\1");v=td.innerHTML.split("\1").map(i=>i|0);}
      if(5==i)ug5(td.cloneNode(true));
      if(6==i)points.push(tag(td,"div").map(
        div=>div.innerHTML
      ));
      var ug8=td=>{repelem(td,"hr","\1");repelem(td,"img","");d=td.innerHTML.split("&nbsp;").join("").split("\1").map(i=>i|0);};
      if(8==i)ug8(td.cloneNode(true));
      if(9==i)token=tag(td,"div").map(e=>e.getAttribute("data-token"))[0];
      //i==6; баллы
      //i==7; место
      //i==9; столбик "Смотреть игру"
    });
    //alert("bef");
    xhr_with_abort('get',"/boombox/data/games/"+token+"?tick=0&fields=tickIndex,players,wizards",e);
    var cb=s=>{
      var t=s.split("Длительность: ")[1].split("</div>")[0];
      tag(tag(e,"td")[0],"a")[0].parentNode.innerHTML+="<br>"+t;
    }
    xhr("get","/game/view/"+id+"?a=get_duration",cb);

    [id,names,v,points,d,token];
    //games[id]=[id,names,v,points,d,token];
    return [id,names,v,points,d,token];
  }
  var out=Array.from(trs).map(f);
  //if(g_auto_add)document.body.innerHTML+="<pre>"+arr2str(out)+"</pre>";
var urls={};
function xhr_with_abort(method,url,elem)
{
  g_counter++;
  var x=new XMLHttpRequest();
  var p=s=>{
    var arr=JSON.parse(s).map(e=>e.name);
    tag(elem,"span").filter(u=>u.className!="day").map(u=>u.innerHTML="<font color="+(arr.indexOf(u.innerHTML)<5?'"#A00"':'"#00A"')+">"+u.innerHTML+"</font>");
    //arr.map((u,id)=>tmp=tmp.split(u).join("<font color="+(id<5?'"red"':'"blue"'));
    //elem.innerHTML=tmp;
    //document.body.innerHTML="<pre>"+
  }
  var f=s=>p("[\n"+s.split('},{').join("},\n{")+"\n]");
  var g=s=>f(s.split(',"players":[')[1].split('],"wizards":')[0]);
  x.onprogress=e=>{
    if(x.responseText.length<1024*2)return;
    if(url in urls)return;
    g(x.responseText);x.abort();
    urls[url]=1;
    g_counter--;
  };
  x.open(method,url,true);x.send();return x;
}

//var x=xhr_with_abort('get',"/boombox/data/games/c1_u94cet2bcuuos0uxoiey6ep4fev?tick=0&fields=tickIndex,players,wizards",0);

function xhr(method,url,callback)
{
  var x=new XMLHttpRequest();
  x.onreadystatechange=function(){if(x.readyState===4){callback(x.responseText,x.status,url);}};
  x.open(method,url);x.send();return x;
}

function make_global(arr)
{
  document["g_funcs"]={};
  var out=[];for(var i=0;i<arr.length;i++){var ex=arr[i];var exn=arr[i].name;document.g_funcs[exn]=arr[i];out.push("var "+exn+"=document.g_funcs."+exn);}
  var code=out.join("\n");var s=document.createElement('script');s.innerHTML=code;document.body.appendChild(s);
}
