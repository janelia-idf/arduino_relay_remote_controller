$(function() {
    $(':button').button();
    $('#toggleRelays').buttonset();
    var uncheckRelays = function() {
        $('#setRelayOn input').removeAttr('checked');
        $('#setRelayOn').buttonset('refresh');
    };
    uncheckRelays();

    $("input:radio[name=relay]").click(function(){
        relay = parseInt($(this).attr("value"));
        Sijax.request('toggleRelay',[relay]);
        uncheckRelays();
    });

    $('#setAllRelaysOn').click(function () {
        Sijax.request('setAllRelaysOn');
    });
    $('#setAllRelaysOff').click(function () {
        Sijax.request('setAllRelaysOff');
    });

});
