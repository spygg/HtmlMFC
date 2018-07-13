var type = 1,xAxisArr=null,
    times = ['2017-03-17','2017-03-24','2017-03-31','2017-04-07','2017-04-07','2017-04-14','2017-03-21'], //初始化直线图x坐标；
    myChartLine = echarts.init(document.getElementById('linerCanvas')), 
    myChartPie = echarts.init(document.getElementById('pieCanvas'));
//将yyyy-mm-dd转换为mm-dd/yyyy;
function datereplace(str){
    var timeArr = []; 
    for(var i=0;i<str.length;i++){
        var tm = str[i].split('-');
        var tms = tm[1]+'-'+tm[2]+'/'+tm[0];
        timeArr.push(tms);
    }
    return timeArr;
}
times = datereplace(times);
//将 mm-dd\nyyyy 还原为 yyyy-mm-dd;
function daterestore1(str){
    var tm = str.split('\n');
    var tms = tm[1]+'-'+tm[0];
    return tms;
}
//将 mm-dd/yyyy 还原为 yyyy-mm-dd;
function daterestore2(str){
    var tm = str.split('/');
    var tms = tm[1]+'-'+tm[0];
    return tms;
}
//获取当前日期 yyyy-mm-dd;
function dateFormat(){
    var myDate = new Date();
    var m = myDate.getMonth()+1;
    if(m<10){
        return myDate.getFullYear()+'-0'+(myDate.getMonth()+1)+'-'+myDate.getDate();
    }else{
        return myDate.getFullYear()+'-'+(myDate.getMonth()+1)+'-'+myDate.getDate();
    }
}

$(function () {    
    var lis = $('#conNav').find('li');
    //切换页面
    lis.on('click',function(){   
      var idx = $(this).index();
      var time = dateFormat();
      if(idx == 0){
          var sendData={
              time:time,
              type:1  
          };
          sendData = JSON.stringify(sendData);
          $("#highStrip").animate({"left":"35px"},200);
          window.external.getLineData(sendData);
          window.external.getPieData(sendData);
      }else if(idx == 1){ //monitor
          $("#highStrip").animate({"left":"140px"},200);
          window.external.getMonitorData();
      }else if(idx == 2){ //pay
          $("#highStrip").animate({"left":"229px"},200);
          window.external.getPayData(sendData);
      }else if(idx == 3){ //discover
          $("#highStrip").animate({"left":"321px"},200);
	  window.external.getDiscoverData(sendData);
      }else if(idx == 4){ //setting
          $("#highStrip").animate({"left":"426px"},200);
      }
      $(this).addClass('high').siblings().removeClass('high');
      $("#contentBox").children('.content').hide().eq(idx).show();
    })
    //STATUS按时间类型切换
    $('.timeBtn').on('click',function(){
        var thisName = $(this).attr('name');
        var time = dateFormat();
        type = thisName;

        $(this).addClass('high').siblings().removeClass('high');
        var sendData = {
            time:time,
            type:thisName
        };
        sendData = JSON.stringify(sendData);
        window.external.getLineData(sendData);
       
        
    });
    //上一日/周/月
    $('#prevBtn').on('click',function(){
        var prevTime = xAxisArr[xAxisArr.length-2];
        prevTime = daterestore2(prevTime);
        var sendData = {
            time:prevTime,
            type:type
        };
        sendData = JSON.stringify(sendData);
        window.external.getLineData(sendData);
    });

    //下一日/周/月
    $('#nextBtn').on('click',function(){
        var nextTime = xAxisArr[xAxisArr.length-1];
        nextTime = daterestore2(nextTime);
        var sendData = {
            time:nextTime,
            type:type
        };
        sendData = JSON.stringify(sendData);
        window.external.getLineData(sendData);
    })
    
    //切换pie状图
    myChartLine.on('click', function (parmas) {
        if(parmas.componentSubType == ''){
            return;
        }else{
            var time = daterestore1(parmas.name);
            var sendData = {
                time:time,
                type:type  
            };
            sendData = JSON.stringify(sendData);
            window.external.getPieData(sendData);
        }        
    })
    //MONITOR按时间类型切换
   /* $('#monitorNav').on('click','p',function(){
        var idx = $(this).index();
        var timeType = $(this).text();
        $(this).addClass('high').siblings().removeClass('high');
	var sendData = {
            time:timeType  
        };
        sendData = JSON.stringify(sendData);
        //window.external.getThisDayData(sendData);
        renderMonitorData();
    });*/

    //pay 选择充值方式
    $('#payWay').on('click','input',function(){
        var curSelectPayNum = $(this).next().next().text();
        var checkboxs = $(this)[0].checked;
        var inputs = $('input');
        curSelectPayNum = curSelectPayNum.substring(1,curSelectPayNum.length);
        $('label').hide();
        for(var i=0;i<inputs.length;i++){
            inputs[i].checked = false;
            $(this)[0].checked = true;
        }
        //console.log($(this),checkboxs);
        //console.log($(this)[0],$(this)[0].checked)
        if(checkboxs){
            $(this).next().show();
            $('#curSelectPayNum').text(curSelectPayNum);
            $(this).parent().addClass('border').siblings().removeClass('border');
        }else{
            $(this).next().hide();
            $('#curSelectPayNum').text(0);
            $(this).parent().removeClass('border');
            $(this)[0].checked = false;
        }
        
        
        
    })

    //slideInRight
    $('#slideIn').on('click',function(){
        if($(this).hasClass('slideInLeft')){
            $(this).addClass('slideInRight').removeClass('slideInLeft');
            $('#conBtn').css('right','0px');
            window.external.slideIn(1); 
        }else{
            $(this).addClass('slideInLeft').removeClass('slideInRight');
            $('#conBtn').css('right','660px')
            window.external.slideIn(0);
        }
    });
    
    //关闭窗口
    $('#closeBtn').on('click',function(){
        window.external.CloseWindow();
    });
    
    //最小化窗口
    $('#minimizeBtn').on('click',function(){
        window.external.MinimizeWindow();
    });

    //拖拽头部
    $('.headerDrive, .TransferCaption').on('mousedown',function(e){
      var x = e.clientX;
      var y = e.clientY;
      window.external.ClickCaption(x + "|" + y);
    })
   
});
