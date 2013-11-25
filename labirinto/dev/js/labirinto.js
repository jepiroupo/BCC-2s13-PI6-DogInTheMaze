dados = {

    labirinto: function (xml){
        //<background>

        $(xml).find("parede").each(function()
        {
            $('<li class="caminho" style="background-image: url(\'imgs/objetos.png\')"></li>').appendTo('#lista');

        });

        var numLis = 0;
        $("#lista").find("li").each(function(){
            numLis += 1;
        });

        init();
    }
}

function init () {

    $("#lista").find("li").click(listaClick);

    var numLis = 0;
        $("#lista").find("li").each(function(){
            numLis += 1;
        });

    for (i=0; i < numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();
        if (pos.left == 0 || pos.left == 1088 || pos.top == 0 || pos.top == 672){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
    }

    function listaClick (e) {
        e.preventDefault();

        navigate($(this).index());
    }

    function navigate(id){
        var button =  $("#lista").find("li")[id];

        if ($(button).hasClass('caminho')){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
        else if ($(button).hasClass('parede')){
            $(button).removeClass('parede');
            $(button).addClass('vermelho');
        }
        else if ($(button).hasClass('vermelho')){
            $(button).removeClass('vermelho');
            $(button).addClass('azul');
        }
        else if ($(button).hasClass('azul')){
            $(button).removeClass('azul');
            $(button).addClass('verde');
        }
        else if ($(button).hasClass('verde')){
            $(button).removeClass('verde');
            $(button).addClass('amarelo');
        }
        else if ($(button).hasClass('amarelo')){
            $(button).removeClass('amarelo');
            $(button).addClass('vermelho_aberto');
        }
        else if ($(button).hasClass('vermelho_aberto')){
            $(button).removeClass('vermelho_aberto');
            $(button).addClass('azul_aberto');
        }
        else if ($(button).hasClass('azul_aberto')){
            $(button).removeClass('azul_aberto');
            $(button).addClass('verde_aberto');
        }
        else if ($(button).hasClass('verde_aberto')){
            $(button).removeClass('verde_aberto');
            $(button).addClass('amarelo_aberto');
        }
        else if ($(button).hasClass('amarelo_aberto')){
            $(button).removeClass('amarelo_aberto');
            $(button).addClass('cachorro');
        }
        else if ($(button).hasClass('cachorro')){
            $(button).removeClass('cachorro');
            $(button).addClass('vermelho_chegada');
        }
        else if ($(button).hasClass('vermelho_chegada')){
            $(button).removeClass('vermelho_chegada');
            $(button).addClass('azul_chegada');
        }
        else if ($(button).hasClass('azul_chegada')){
            $(button).removeClass('azul_chegada');
            $(button).addClass('verde_chegada');
        }
        else if ($(button).hasClass('verde_chegada')){
            $(button).removeClass('verde_chegada');
            $(button).addClass('amarelo_chegada');
        }
        else if ($(button).hasClass('amarelo_chegada')){
            $(button).removeClass('amarelo_chegada');
            $(button).addClass('caminho');
        }

        var pos = $(button).offset();
        console.log("left: " + pos.left + " top: " + pos.top);
    }
}

var string;
string = "";

var stringXML;
stringXML = "<dados>\r\n";

function gerarXML(){

    var numLis = 0;
    $("#lista").find("li").each(function(){
        numLis += 1;
    });
    for (i=0; i < numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();

        if ($(button).hasClass('caminho')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "00"; // 0 = caminho
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>caminho</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('parede')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "01"; // 1 = parede
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>parede</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('vermelho')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "02"; // 2 = vermelho
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>vermelho</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('azul')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "03"; // 3 = azul
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>azuk</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('verde')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "04"; // 4 = verde
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>verde</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('amarelo')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "05"; // 5 = amarelo
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>amarelo</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('vermelho_aberto')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "06"; // 6 = vermelho aberto
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>vermelho_aberto</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('azul_aberto')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "07"; // 7 = azul aberto
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>azul_aberto</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('verde_aberto')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "08"; // 8 = verde aberto
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>verde_aberto</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('amarelo_aberto')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "09"; // 9 = amarelo aberto
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>amarelo_aberto</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('cachorro')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "10"; // 10 = posição inicial do cachorro
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>cachorro</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('vermelho_chegada')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "11"; // 11 = posição de chegada jogador vermelho
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>vermelho_chegada</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('azul_chegada')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "12"; // 12 = posição de chegada do jogador azul
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>azul_chegada</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('verde_chegada')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "13"; // 13 = posição de chegada do jogador verde
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>verde_chegada</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('amarelo_chegada')){
            if (pos.left >= 0 && pos.left < 10){
                string += "000" + pos.left;
            }else if (pos.left >= 10 && pos.left < 100){
                string += "00" + pos.left;
            }else if (pos.left >= 100 && pos.left < 1000){
                string += "0" + pos.left;
            }else{
                string += pos.left;
            }

            if (pos.top >= 0 && pos.top < 10){
                string += "000" + pos.top;
            }else if (pos.top >= 10 && pos.top < 100){
                string += "00" + pos.top;
            }else if (pos.top >= 100 && pos.top < 1000){
                string += "0" + pos.top;
            }else{
                string += pos.top;
            }

            string += "14"; // 14 = Posição de chegada do jogador amarelo
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>amarelo_chegada</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }

    }
    stringXML += "</dados>";
    console.log(string);
    escreverArquivo();
    escreverXML();
}

function escreverArquivo() {  
    var fso  = new ActiveXObject("Scripting.FileSystemObject");
    var fh = fso.CreateTextFile("C:/Users/Jessica/Documents/GitHub/projeto_interativo_vi/labirinto/dev/labirinto.txt", true); 
    fh.WriteLine(string);
    fh.Close(); 
}

function escreverXML() {  
    var fso  = new ActiveXObject("Scripting.FileSystemObject");
    var fh = fso.CreateTextFile("C:/Users/Jessica/Documents/GitHub/projeto_interativo_vi/labirinto/dev/labirinto.xml", true); 
    fh.WriteLine(stringXML);
    fh.Close(); 
}