//获取Liner图数据,渲染页面;
function showLiner(Allfiles){
    /*Allfiles = {
        code:1,
        time:'month',
        xAxis:['One','Two','Three','Four','Five'],
        data: [254,545,167,92,45]
    };*/
    var arr = [],xAxisLast,curDate;    
    Allfiles = JSON.parse(Allfiles);
    xAxisArr = datereplace(Allfiles.xAxis);
    xAxisLast = xAxisArr[xAxisArr.length-1];
    curDate = dateFormat();
    
    //判断是否需要显示nextBtn按钮
    xAxisLast = daterestore2(xAxisLast).replace(/-/g,'');
    curDate = curDate.replace(/-/g,'');
    if(xAxisLast == curDate){
        $('#nextBtn').hide();
    }else{
        $('#nextBtn').show();
    }
    //为optionLine附值；
    for(var i=0;i<Allfiles.data.length;i++){
        arr.push({xAxis: i, yAxis: Allfiles.data[i]})
    }
    optionLine.series[0].animation = false,
    optionLine.xAxis[0].data = xAxisArr.map(function (str) {
                return str.replace('/', '\n')
            });
    optionLine.series[0].data = Allfiles.data;
    optionLine.series[0].markPoint.data = arr;
    myChartLine.setOption(optionLine); 

}

//获取Pie图数据,渲染页面;
function showPie(Allfiles){
    /*Allfiles = {
        code:1,
        time:'Fri',
        data:[
                  {value:345, name:'Others'},
                  {value:110, name:'iTunes'},
                  {value:234, name:'Netflix'},
                  {value:935, name:'Dropbox'},
                  {value:98, name:'Chrome'}
              ]
    };*/
    Allfiles = JSON.parse(Allfiles);
    optionPie.series[0].data = Allfiles.data;
    myChartPie.setOption(optionPie);

}

//获取monitor当天数据,渲染页面;
function renderMonitorData(Allfiles){
    /*Allfiles = {
        code:1,
        name:'Fri',
        data:[
                  {url:'', name:'360se.exe',safetyLevel:'安全',updataSpeed:'23.4KB',updataLimit:'无限制',updataTraffic:'34MB',downloadSpeed:'43.4KB',downloadLimit:'无限制',downloadTraffic:'14MB',linkNum:9,manage:''},
                  {url:'', name:'360se.exe',safetyLevel:'安全',updataSpeed:'2.4KB',updataLimit:'无限制',updataTraffic:'4MB',downloadSpeed:'53.4KB',downloadLimit:'无限制',downloadTraffic:'65MB',linkNum:2,manage:''},
                  {url:'', name:'360se.exe',safetyLevel:'安全',updataSpeed:'3.4KB',updataLimit:'无限制',updataTraffic:'3MB',downloadSpeed:'64KB',downloadLimit:'无限制',downloadTraffic:'7MB',linkNum:6,manage:''},
                  {url:'', name:'360se.exe',safetyLevel:'安全',updataSpeed:'78.4KB',updataLimit:'无限制',updataTraffic:'14MB',downloadSpeed:'94KB',downloadLimit:'无限制',downloadTraffic:'9MB',linkNum:7,manage:''},
                  {url:'', name:'360se.exe',safetyLevel:'安全',updataSpeed:'9.4KB',updataLimit:'无限制',updataTraffic:'34MB',downloadSpeed:'4.4KB',downloadLimit:'无限制',downloadTraffic:'14MB',linkNum:3,manage:''},
                  {url:'', name:'360se.exe',safetyLevel:'安全',updataSpeed:'2.4KB',updataLimit:'无限制',updataTraffic:'34MB',downloadSpeed:'3.4KB',downloadLimit:'无限制',downloadTraffic:'14MB',linkNum:1,manage:''}
              ]
    };*/
    Allfiles = JSON.parse(Allfiles);
    $('#monitorList').html('');
    for(var i=0;i<Allfiles.data.length;i++){
        var html = '<li class="monitorlis">'+
                              '<span>'+Allfiles.data[i].name+'</span>'+
                              '<span>'+Allfiles.data[i].safetyLevel+'</span>'+
                              '<span>'+Allfiles.data[i].updataSpeed+'</span>'+
                              '<span>'+Allfiles.data[i].downloadSpeed+'</span>'+
                              '<span>'+Allfiles.data[i].updataLimit+'</span>'+
                              '<span>'+Allfiles.data[i].downloadLimit+'</span>'+
                              '<span>'+Allfiles.data[i].updataTraffic+'</span>'+
                              '<span>'+Allfiles.data[i].downloadTraffic+'</span>'+
                              '<span>'+Allfiles.data[i].linkNum+'</span>'+
                              '<span class="manage"></span>'+
                        '</li>'
        $('#monitorList').append(html);
    }

};

//获取pay页面数据，渲染；
function renderPayData(Allfiles){
    /*Allfiles = {
        code:1,
        iccId:'XXXXXX 0MFSS YYGXX XXXXX',
        data:[
                  {
                    price:180, 
                    favorable:'优惠', 
                    preferentialPolicy:'送50元话费', 
                    paySize:'100G',
                    validityPeriod:'360天有效' 
                  },
                  {
                    price:10, 
                    favorable:'', 
                    preferentialPolicy:'', 
                    paySize:'100G',
                    validityPeriod:'360天有效' 
                  },
                  {
                    price:180, 
                    favorable:'优惠', 
                    preferentialPolicy:'', 
                    paySize:'100G',
                    validityPeriod:'360天有效' 
                  },
                  {
                    price:100, 
                    favorable:'惠', 
                    preferentialPolicy:'', 
                    paySize:'10G', 
                    validityPeriod:'360天有效' 
                  }                 
            ]
    };*/
    
    var payData = Allfiles.data;
    Allfiles = JSON.parse(Allfiles);
    $('#iccId').text(Allfiles.iccId);
    $('#payWayBox').html('');
    for(var i = 0;i < payData.length;i++){
        var payHtml1 = '<div class="pay">'+
                        '<input type="checkbox" id="checkbox_'+i+'">'+
                        '<label for="checkbox_'+i+'"></label>'+
                        '<span class="payInfo price">￥'+payData[i].price+'</span>'+
                        '<span class="payInfo paySize">'+payData[i].paySize+'</span>'+
                        '<span class="payInfo validityPeriod">'+payData[i].validityPeriod+'</span>'+
                     '</div>';
        var payHtml2 = '<div class="pay">'+
                        '<input type="checkbox" id="checkbox_'+i+'">'+
                        '<label for="checkbox_'+i+'"></label>'+
                        '<span class="payInfo price">￥'+payData[i].price+'</span>'+
                        '<span class="payInfo favorable">'+payData[i].favorable+'</span>'+
                        '<span class="payInfo preferentialPolicy">'+payData[i].preferentialPolicy+'</span>'+
                        '<span class="payInfo paySize">'+payData[i].paySize+'</span>'+
                        '<span class="payInfo validityPeriod">'+payData[i].validityPeriod+'</span>'+
                     '</div>';
        if(payData[i].favorable == ''){
            $('#payWayBox').append(payHtml1);
        }else{
            $('#payWayBox').append(payHtml2);
        }
        
    }
};

//获取discover页面数据，渲染；
function renderDiscoverData(Allfiles){
    /*Allfiles = {
        data:[
                  {
                    name:'联想笔记本', 
                    description:'联想(Lenovo)小新Air 12.2英寸13.4mm超轻薄笔记本电脑(6Y30 4G 128G SSD IPS FHD WIN10 WiFi)金', 
                    url:'https://item.jd.com/3178510.html', 
                    imgUrl:'images/1.jpg'
                  },
                  {
                    name:'联想笔记本', 
                    description:'联想(Lenovo)小新Air 12.2英寸13.4mm超轻薄笔记本电脑(6Y30 4G 128G SSD IPS FHD WIN10 WiFi)金', 
                    url:'https://item.jd.com/3178510.html', 
                    imgUrl:'images/1.jpg'
                  },
                  {
                    name:'联想笔记本', 
                    description:'联想(Lenovo)小新Air 12.2英寸13.4mm超轻薄笔记本电脑(6Y30 4G 128G SSD IPS FHD WIN10 WiFi)金', 
                    url:'https://item.jd.com/3178510.html', 
                    imgUrl:'images/1.jpg'
                  }
            ]
    };*/
    
    var discoverData = Allfiles.data;
    Allfiles = JSON.parse(Allfiles);
    $('#discoverBox').html('');
    for(var i = 0;i < discoverData.length;i++){
      console.log(discoverData.length)
        var discoverHtml = '<dl>'+
                              '<dt>'+
                                 '<span>'+discoverData[i].name+'</span>'+
                                 '<span class="payConInfo" title="'+discoverData[i].description+'">'+discoverData[i].description+'</span>'+
                                 '<a class="payViewdetails" target="_blank" href="'+discoverData[i].url+'">查看详情</a>'+
                              '</dt>'+
                              '<dd>'+
                                 '<img class="payImg" src="'+discoverData[i].imgUrl+'">'+
                              '</dd>'+
                           '</dl>';
        $('#discoverBox').append(discoverHtml);
     }
    //图片居中
    var payImg = $('.payImg');
    for(var i=0;i<payImg.length;i++){
        var wid = $(payImg[i]).width();
        var hei = $(payImg[i]).height();
        if(wid>=hei){
            $(payImg[i]).css('width','100%');
        }else{
            $(payImg[i]).css({'height':'80%','margin-top':'10%'});
        }
    }
};