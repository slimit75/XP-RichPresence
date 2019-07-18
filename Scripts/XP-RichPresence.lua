-- Configuration
spdDisagree = true -- Enables SPD DISAGREE warning.
altDisagree = true -- Enables ALT DISAGREE warning.

-- Program, dont touch unless you know what you are doing!
discordRPC = require "discordRPC"
startTime = os.time()
aircraft = "N/A"
image = "xp"
version = "v0.6b"

function refresh()
    dataref("acf", "sim/aircraft/view/acf_descrip", "readable")
    dataref("acfIcao", "sim/aircraft/view/acf_ICAO", "readable")
    dataref("tailNum", "sim/aircraft/view/acf_tailnum", "readable")
    dataref("kts", "sim/flightmodel/position/indicated_airspeed", "readable")
    dataref("kts2", "sim/flightmodel/position/indicated_airspeed2", "readable")
    dataref("alt", "sim/cockpit2/gauges/indicators/altitude_ft_pilot", "readable")
    dataref("alt2", "sim/cockpit2/gauges/indicators/altitude_ft_copilot", "readable")

    if (spdDisagree == true) then
        if (kts ~= kts2) then
            kts = "SPD DISAGREE"
        else
            kts = math.floor(kts) .. "kts"
        end
    else
        kts = math.floor(kts) .. "kts"
    end

    if (altDisagree == true) then
        if (alt ~= alt2) then
            altitude = "ALT DISAGREE"
        else
            altitude = math.floor(alt) .. "ft"
        end
    else
        altitude = math.floor(alt) .. "ft"
    end

    if (acfIcao == "E170") or (acfIcao == "E175") or (acfIcao == "E190") or (acfIcao == "E195") then -- Embrear E-Jets
        aircraft = "Embraer " .. acfIcao
        image = "e-jets"
        altDisagree = false
    elseif (acfIcao == "DR40") then -- Robin DR400/DR401
        aircraft = "Robin DR401"
        image = "dr40"
    elseif (acfIcao == "C172") then -- Cessna 172
        aircraft = "Cessna 172 Skyhawk"
        image = "c172"
    elseif (acfIcao == "B733") or (acfIcao == "B734") or (acfIcao == "B735") or (acfIcao == "B736") or (acfIcao == "B737") or (acfIcao == "B738") or (acfIcao == "B739") then -- 737 Classic & 737NG
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 737-" .. temp .. "00"
        image = "737ng"
    elseif (acfIcao == "B744") then -- Boeing 747-400
        aircraft = "Boeing 747-400"
        image = "747"
    elseif (acfIcao == "B748") then -- Boeing 747-8
        aircraft = "Boeing 747-8"
        image = "747"
    elseif (acfIcao == "A318") or (acfIcao == "A319") or (acfIcao == "A320") or (acfIcao == "A321") then -- Airbus A320 Family
        aircraft = "Airbus " .. acfIcao
        image = "a320"
    elseif (acfIcao == "B752") or (acfIcao == "B753") then -- Boeing 757
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 757-" .. temp .. "00"
        image = "b757"
        altDisagree = false
    elseif (acfIcao == "MD82") or (acfIcao == "MD88") then -- MD80
        aircraft = "McDonnell Douglass " .. acfIcao
        image = "md88"
    elseif (acfIcao == "B712") then -- Boeing 717-200
        aircraft = "Boeing 717-200"
        image = "md88"
    elseif (acfIcao == "D328") or (acfIcao == "J328") then -- Dornier 328/328JET
        aircraft = "Dornier 328"
        image = "d328"
    elseif (acfIcao == "B772") or (acfIcao == "B773") then -- Boeing 777-200/-300
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 777-" .. temp .. "00"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "UAE") then -- Support for Chai112/Chai112-s-Boeing-777-300ER
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 777-300ER"
        image = "773"
        acfIcao = "B77W"
        altDisagree = false
    elseif (acfIcao == "B778") or (acfIcao == "B779") then -- Boeing 777-8/-9
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 777-" .. temp
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B77L") then -- Boeing 777F / 777-200LR
        aircraft = "Boeing 777-200LR / 777F"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B77W") then -- Boeing 777-300ER
        aircraft = "Boeing 777-300ER"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B762") or (acfIcao == "B763") then -- Boeing 767-200/300
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 767-" .. temp .. "00"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B764") then -- Boeing 767-400ER
        aircraft = "Boeing 767-400ER"
        image = "773"
        altDisagree = false
    elseif (acfIcao == "B788") or (acfIcao == "B789") then -- Boeing 787-8/-9
        temp = string.sub(acfIcao, 4, -1)
        aircraft = "Boeing 787-" .. temp
        image = "787"
        altDisagree = false
    elseif (acfIcao == "B78X") then -- Boeing 787-10
        aircraft = "Boeing 787-10"
        image = "787"
        altDisagree = false
    else
        aircraft = acf
    end

    if image ~= "xp" then
        discordRPC.updatePresence({
            ["state"] = altitude .. ", " .. kts,
            ["details"] = aircraft,
            ["startTimestamp"] = startTime,
            ["largeImageKey"] = image,
            ["largeImageText"] = acfIcao,
            ["smallImageKey"] = "xp",
            ["smallImageText"] = version
        })
    else
        discordRPC.updatePresence({
            ["state"] = altitude .. ", " .. kts,
            ["details"] = aircraft,
            ["startTimestamp"] = startTime,
            ["largeImageKey"] = image,
            ["largeImageText"] = acfIcao,
            ["smallImageText"] = version
        })
    end
end

function run()
    discordRPC.initialize("579668847846752266", false, "269950")
    do_on_exit("discordRPC.clearPresence()")
    do_often("refresh()")
end

local ok = xpcall(run, function(err)
    logMsg(err)
end)