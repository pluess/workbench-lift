function updateSliderPWM(element) {
    var sliderValue = $(element).val();
    $("#text_" + element.id).html(sliderValue);
    var mode = $("#mode").val();
    console.log("element.id=" + element.id)
    console.log("sliderValue=" + sliderValue);
    console.log("mode=" + mode);
    $.ajax(
        {
            url: "/setpwm",
            data: {
                motor: element.id,
                pwm: sliderValue,
                mode: mode
            },
            type: "GET"
        }
    )
    // var xhr = new XMLHttpRequest();
    // xhr.open("GET", "/set-pwm-" + element.id + "?pwm=" + sliderValue + "&mode=" + mode, true);
    // xhr.send();
}

function resetFunction() {
    $("#allpwm").val(50).trigger("change");
    for (var i = 1; i <= 4; i++) {
        $("#motor" + i).val(50).trigger("change");
    }
}
